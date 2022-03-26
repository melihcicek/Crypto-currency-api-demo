#ifndef COINCAP_MODEL_H
#define COINCAP_MODEL_H

#include "coin.h"
#include <QAbstractTableModel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class coincap_model : public QAbstractTableModel
{
    Q_OBJECT;
public:

    coincap_model(QObject *parent=nullptr);

    QString get_coin_id(int idx) const;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void start_get_coin_list();

private:
    QString m_get_coin_list_api{"https://api.coincap.io/v2/assets"};
    std::vector<coin> m_coin_list;

    QNetworkAccessManager * m_net_manager;
    QNetworkReply * m_net_reply;
    QByteArray * m_data_buffer;
    constexpr static int COLUMN_CNT = 5;

    enum class column_name{
        id,
        symbol,
        name,
        price_usd,
        change
    };

private slots:
    void dataReadyRead();
    void dataReadFinished();
signals:
    void dataReadFinish();


};

#endif // COINCAP_MODEL_H
