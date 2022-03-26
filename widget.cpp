#include "widget.h"
#include "ui_widget.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QString>
#include <QMessageBox>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "currency_widget.h"
#include "coincap_model.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), m_net_manager{ new QNetworkAccessManager(this)},
      m_net_reply {nullptr}, m_data_buffer{new QByteArray}, m_currency_widget{new currency_widget}
{
    ui->setupUi(this);

    ui->horizontalLayout->addWidget(m_currency_widget);
    m_coin_list_model = new coincap_model(this);
    ui->tableViewCoin->setModel(m_coin_list_model);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::refresh_info()
{
    m_coin_list_model->start_get_coin_list();

    QNetworkRequest request;
    request.setUrl(coin_api_url);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    m_net_reply = m_net_manager->get(request);

    connect(m_net_reply, &QIODevice::readyRead, this, &Widget::dataReadyRead);
    connect(m_net_reply, &QNetworkReply::finished, this, &Widget::dataReadFinished);


}

void Widget::dataReadyRead()
{
    m_data_buffer->append(m_net_reply->readAll());
}

void Widget::dataReadFinished()
{
    if( m_net_reply->error()) {
        QMessageBox::warning(this, "Error" ,m_net_reply->errorString());
    }
    else {
        //Turn the data into a json document
        QJsonObject object;
        QVariantMap map;
        auto doc = QJsonDocument::fromJson(*m_data_buffer);
        auto json_obj = doc.object();

        auto array = json_obj["data"].toArray();
        m_currency_widget->clear();

        for ( int i = 0; i < array.size(); i++) {
            object = array.at(i).toObject();
            map = object.toVariantMap();
            m_currency_widget->update_series(i, map["priceUsd"].toDouble());
        }

    }

    m_data_buffer->clear();
}

void Widget::on_tableViewCoin_clicked(const QModelIndex &index)
{
    QString coin_id = m_coin_list_model->get_coin_id(index.row());
    coin_api_url = m_currency_widget->coin_url_p1.toString() + coin_id +
            m_currency_widget->coin_url_p2.toString();
     qDebug()<<coin_api_url;

     m_currency_widget->set_title(coin_id);
    refresh_info();
}
