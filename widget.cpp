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
#include "btcwidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), m_net_manager{ new QNetworkAccessManager(this)},
      m_net_reply {nullptr}, m_data_buffer{new QByteArray}, m_btc_widget{new BtcWidget}
{
    ui->setupUi(this);

    ui->horizontalLayout->addWidget(m_btc_widget);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_get_clicked()
{
    const QUrl bitcoin_api_url("https://api.coincap.io/v2/assets/bitcoin/history?interval=d1");
    QNetworkRequest request;
    request.setUrl(bitcoin_api_url);
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
        qDebug() << "Data fetch finished";

        //Turn the data into a json document
        QJsonObject object;
        QVariantMap map;
        auto doc = QJsonDocument::fromJson(*m_data_buffer);
        auto json_obj = doc.object();

        auto array = json_obj["data"].toArray();
        m_btc_widget->clear();

        for ( int i = 0; i < array.size(); i++) {
            object = array.at(i).toObject();
            map = object.toVariantMap();
            m_btc_widget->update_series(i, map["priceUsd"].toDouble());
        }
    }

    m_data_buffer->clear();
}


