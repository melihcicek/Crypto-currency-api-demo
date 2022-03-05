#include "btcwidget.h"
#include "ui_btcwidget.h"
#include <QVBoxLayout>
#include<QDebug>

using namespace QtCharts;

BtcWidget::BtcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BtcWidget)
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

BtcWidget::~BtcWidget()
{
    delete ui;
}

void BtcWidget::update_series(int idx, int val)
{
    series->append(idx, val);
    //qDebug()<<QString::number(val);
}

void BtcWidget::clear()
{
    series->clear();
}
