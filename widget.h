#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QNetworkAccessManager;
class QNetworkReply;
class QChartView;
class BtcWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_get_clicked();
    void dataReadyRead();
    void dataReadFinished();

private:
    Ui::Widget *ui;
    QNetworkAccessManager * m_net_manager;
    QNetworkReply * m_net_reply;
    QByteArray * m_data_buffer;
    BtcWidget* m_btc_widget;
};
#endif // WIDGET_H
