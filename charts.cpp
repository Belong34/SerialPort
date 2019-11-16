#include "charts.h"
#include "ui_charts.h"
#include <qmath.h>
#include "QTime"
#include "QDebug"
#include "qmath.h"
#include "QValueAxis"
#include "QDateTimeAxis"
#include "QRandomGenerator"

Charts::Charts(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Charts)
{
    ui->setupUi(this);

    m_timer.setInterval(1000);//设置定时器间隔
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(RealtimeDataSlot()));

    m_x=0;
    m_y=0;

    chart.setTheme(QChart::ChartThemeBlueCerulean);//设置系统主题
    //chart.setTitle("动态正弦波形图");//设置标题
    chart.setTitleFont(QFont("微软雅黑",10));
    chart.legend()->hide();//隐藏图例


    QPen green(Qt::yellow);//画笔颜色
    green.setWidth(2);
    m_series.setPen(green);
    m_series.append(m_x, m_y);

    chart.addSeries(&m_series);
    chart.createDefaultAxes();
    chart.setAxisX(&m_axis,&m_series);
    m_axis.setTickCount(5);
    chart.axisX()->setRange(0,10);//设置坐标范围
    chart.axisY()->setRange(-1, 1);



    QChartView *chartView = new QChartView(&chart);
    QGridLayout *baseLayout = new QGridLayout(); //便于显示，创建网格布局

    chartView->setRenderHint(QPainter::Antialiasing);

    baseLayout->addWidget(chartView, 0, 0);
    //ui->widgetWaveForm->setLayout(baseLayout); //显示到QWidget控件
    ui->listWidget->setLayout(baseLayout);  //  listWidget是在界面中提升的控件对象

    m_timer.start();//启动定时器
}

Charts::~Charts()
{
    delete ui;
}
void Charts::RealtimeDataSlot()
{
    qreal x = chart.plotArea().width()/m_axis.tickCount();
    qreal y = 10/m_axis.tickCount();
    m_x += y;
    m_y=sin(m_x);
    m_series.append(m_x, m_y);
    chart.scroll(x/2, 0);
    /*if (m_x == 100)
        m_timer.stop();*/
}
void Charts::creatData()
{

}
