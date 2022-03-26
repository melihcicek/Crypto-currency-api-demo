#include "coincap_model.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

coincap_model::coincap_model(QObject *parent) : QAbstractTableModel(parent),
    m_net_manager{ new QNetworkAccessManager(this)}, m_net_reply {nullptr}, m_data_buffer{new QByteArray}
{
    start_get_coin_list();
}

void coincap_model::start_get_coin_list()
{
    QNetworkRequest request;

    request.setUrl(m_get_coin_list_api);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    m_net_reply = m_net_manager->get(request);

    connect(m_net_reply, &QIODevice::readyRead, this, &coincap_model::dataReadyRead);
    connect(m_net_reply, &QNetworkReply::finished, this, &coincap_model::dataReadFinished);
}

QString coincap_model::get_coin_id(int idx) const
{
    return m_coin_list[idx].id();
}

int coincap_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_coin_list.size() -1;
}

int coincap_model::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return COLUMN_CNT;
}

QVariant coincap_model::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_coin_list.size())
        return QVariant();

    if(role == Qt::DisplayRole || role == Qt::EditRole){

        const coin& r = m_coin_list[index.row()];

        switch(index.column())
        {
        case 0: return r.id();
        case 1: return r.symbol();
        case 2: return r.name();
        case 3: return r.price_usd();
        case 4: return r.change_percent24Hr();
        }
    }

    return  QVariant();
}

QVariant coincap_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    column_name column = static_cast<column_name>(section);

    if (orientation == Qt::Horizontal) {
        switch (column) {
        case column_name::id : return QString("id");
        case column_name::symbol : return QString("Symbol");
        case column_name::name : return QString("Name");
        case column_name::price_usd : return QString("Price Usd");
        case column_name::change : return QString("Change");
        }
    }
    // vertical rows
    // return QString("Coin %1").arg(section);
    return QVariant();
}

Qt::ItemFlags coincap_model::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QAbstractItemModel::flags(index);
    }
    return QAbstractItemModel::flags(index);
}


void coincap_model::dataReadyRead()
{
    m_data_buffer->append(m_net_reply->readAll());
}

void coincap_model::dataReadFinished()
{
    if( m_net_reply->error()) {
        qDebug()<<m_net_reply->errorString();
    }
    else {
        //Turn the data into a json document
        QJsonObject object;
        QVariantMap map;

        auto doc = QJsonDocument::fromJson(*m_data_buffer);
        auto json_obj = doc.object();
        auto array = json_obj["data"].toArray();

        m_coin_list.clear();

        beginRemoveRows(QModelIndex(), 0, array.size());
        endRemoveRows();

        beginInsertRows(QModelIndex(), 0, array.size());
        for ( int i = 0; i < array.size(); i++) {
            object = array.at(i).toObject();
            map = object.toVariantMap();

            m_coin_list.emplace_back(map["id"].toString(),  map["symbol"].toString(),
                    map["name"].toString(), map["priceUsd"].toDouble(), map["changePercent24Hr"].toDouble());

        }
        endInsertRows();

    }

    emit dataReadFinish();
    emit dataChanged(index(0, 0), index( m_coin_list.size() , COLUMN_CNT));
    m_data_buffer->clear();

}
