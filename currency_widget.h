#ifndef BTCWIDGET_H
#define BTCWIDGET_H

#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>


namespace Ui {
class currency_widget;
}

class currency_widget : public QWidget
{
    Q_OBJECT

public:
    explicit currency_widget(QWidget *parent = nullptr);
    ~currency_widget();
    void update_series(int idx, int val);
    void clear();

    const QUrl coin_url_p1;
    const QUrl coin_url_p2;
    void set_axis_range(const int min, const int max);
    void set_title(QString title);
private:
    Ui::currency_widget *ui;
    QtCharts::QChartView *m_charview;
    QtCharts::QChart *m_chart;
    QtCharts::QLineSeries* series;

};

#endif // BTCWIDGET_H
