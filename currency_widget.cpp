#include "currency_widget.h"
#include "ui_btcwidget.h"
#include <QVBoxLayout>
#include<QDebug>

using namespace QtCharts;

currency_widget::currency_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::currency_widget), coin_url_p1 ("https://api.coincap.io/v2/assets/"),
    coin_url_p2 ("/history?interval=d1")
{
    ui->setupUi(this);

    series = new  QLineSeries();

    m_chart = new QChart();
    m_chart->legend()->hide();
    m_chart->legend()->setVisible(false);
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();

    m_chart->axes(Qt::Horizontal).first()->setRange(0, 364);
    m_chart->axes(Qt::Vertical).first()->setRange(20000, 70000);

    m_chart->setTitle("BTC");

    m_charview = new QChartView(m_chart);
    m_charview->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_charview);
    setLayout(layout);
}

currency_widget::~currency_widget()
{
    delete ui;
}

void currency_widget::update_series(int idx, int val)
{
    series->append(idx, val);
}

void currency_widget::clear()
{
    series->clear();
}

void currency_widget::set_axis_range(const int min, const int max)
{
    m_chart->axes(Qt::Vertical).first()->setRange(min, max);

}

void currency_widget::set_title(QString title)
{
    m_chart->setTitle(title);
}
