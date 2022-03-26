#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUrl>
class QNetworkAccessManager;
class QNetworkReply;
class QChartView;
class currency_widget;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class coincap_model;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void dataReadyRead();
    void dataReadFinished();

    void on_tableViewCoin_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    QNetworkAccessManager * m_net_manager;
    QNetworkReply * m_net_reply;
    QByteArray * m_data_buffer;
    currency_widget* m_currency_widget;
    coincap_model* m_coin_list_model;
    QUrl coin_api_url;

    void refresh_info();

};
#endif // WIDGET_H
