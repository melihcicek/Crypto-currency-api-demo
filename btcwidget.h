#ifndef BTCWIDGET_H
#define BTCWIDGET_H

#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>


namespace Ui {
class BtcWidget;
}

class BtcWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BtcWidget(QWidget *parent = nullptr);
    ~BtcWidget();
    void update_series(int idx, int val);
    void clear();
private:
    Ui::BtcWidget *ui;
    QtCharts::QChartView *m_charview;
    QtCharts::QChart *m_chart;
    QtCharts::QLineSeries* series;
};

#endif // BTCWIDGET_H
