#include "chart2.h"
#include "ui_chart2.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QTime>
#include <QtCore/QDebug>
#include <QPen>
#include<QPainter>
#include<QtCharts\QLegendMarker>
#include<qmath.h>
#include <widget.h>
int timeId;

chart2::chart2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chart2)
{
    ui->setupUi(this);
    m_chart = new QChart;

    this->data_n=0;
    ui->listWidget->setChart(m_chart);//已经提升listWidget为QChartView
    //m_chartView->setRubberBand(QChartView::RectangleRubberBand);  //矩形缩放
    //设置x坐标轴
    axisX = new QValueAxis;
    //axisX->setRange(0, 1000);  //范围
    axisX->setLabelFormat("%d"); //图例的格式  %d为十进制显示
    axisX->setGridLineVisible(true);//网格
    //axisX->setTickCount(11);   //主要刻度

    axisX->setTitleText("时间/(s)");//标题
    //设置y坐标轴
    axisY = new QValueAxis;
    axisY->setRange(0, 1000);
    axisY->setLabelFormat("%d");
    axisY->setGridLineVisible(true);
    axisY->setTickCount(10);
    axisY->setMinorTickCount(5);
    axisY->setTitleText("data");

    m_chart->addAxis(axisX, Qt::AlignBottom);  //将坐标轴加到chart上，居下
    m_chart->addAxis(axisY, Qt::AlignLeft);//居左

   //m_chart->setTitle("example of chart");   //设置图表标题
    //m_chart->setAnimationOptions(QChart::SeriesAnimations);  //曲线动画模式，不能启用这一项或是选择这个选项，这个会导致曲线闪烁
    m_chart->legend()->setVisible(true);  //设置图例可见
  //生成一小段数据列表用作绘图初始数据
    QList<QPointF> mydata1;
       mydata1.append(QPointF(0, 0));
    addSeries(mydata1); //增加一条曲线，数据集为mydata1
   connectMarkers();  //将曲线与图例连接起来，可以勾选进行显示与隐藏

    m_chart->setAxisX(axisX, m_serieslist.first());  //将x和y坐标轴与第一条曲线连接
    m_chart->setAxisY(axisY, m_serieslist.first());
    timeId = startTimer(1000);    //qobject中的函数，设置定时器时间间隔

}
QList<QPointF> chart2::data;
int chart2::data_n;
chart2::~chart2()
{
 delete ui;
}


void chart2::addSeries(QList<QPointF> &data)  //用于新增曲线
{

    QSplineSeries *series = new QSplineSeries();
    m_serieslist.append(series);//将曲线加到曲线列表中进行管理
    series->setName(QString("line " + QString::number(m_serieslist.count()))); //设置曲线对应的名字，用于图例显示
    series->append(data);  //将数据加到曲线中
    m_chart->addSeries(series);//将曲线增入chart中
    axisX->setRange(0, series->count());  //坐标轴初始范围为图表中的数据数。 这个在绘制多条曲线中需注释

}

void chart2::removeSeries()  //移除一条曲线
{
    // Remove last series from chart
    if (m_serieslist.count() > 0) {
        QSplineSeries *series = m_serieslist.last();
        m_chart->removeSeries(series);
        m_serieslist.removeLast();
        delete series;
    }
}

void chart2::connectMarkers()  //将槽函数与图例的鼠标点击事件连接起来
{
    // Connect all markers to handler
    foreach(QLegendMarker* marker, m_chart->legend()->markers()) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, &QLegendMarker::clicked, this, &chart2::handleMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked, this, &chart2::handleMarkerClicked);
    }
}

void chart2::disconnectMarkers()
{
    foreach(QLegendMarker* marker, m_chart->legend()->markers()) {
        QObject::disconnect(marker, &QLegendMarker::clicked, this, &chart2::handleMarkerClicked);
    }
}

void chart2::handleMarkerClicked()//图例点击事件
{
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
    Q_ASSERT(marker);
    //![3]

    //![4]
    switch (marker->type())
        //![4]
    {
    case QLegendMarker::LegendMarkerTypeXY:
    {
        //![5]

        marker->series()->setVisible(!marker->series()->isVisible());

        marker->setVisible(true);
        //![5]

        //![6]
        qreal alpha = 1.0;

        if (!marker->series()->isVisible()) {
            alpha = 0.5;
        }

        QColor color;
        QBrush brush = marker->labelBrush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setLabelBrush(brush);

        brush = marker->brush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setBrush(brush);

        QPen pen = marker->pen();
        color = pen.color();
        color.setAlphaF(alpha);
        pen.setColor(color);
        marker->setPen(pen);

        //![6]
        break;
    }
    default:
    {
        qDebug() << "Unknown marker type";
        break;
    }
    }
}

QList<QPointF> chart2::setdata()  //设置图表数据的函数接口
{
    QList<QPointF> datalist;
    for (int i = 0; i < 500; i++)
        datalist.append(QPointF(i, i*0.01));

    return datalist;
}

void chart2::timerEvent(QTimerEvent *event)    //定时器事件的重构
{
    if (event->timerId() == timeId)//定时器时间到，模拟数据填充
    {
        static QTime dataTime(QTime::currentTime());
        long int eltime = dataTime.elapsed();  //经过的时间
        static int lastpointtime = 1;
        int size = (eltime - lastpointtime);//数据个数
        if (isVisible())
        {
            this->data.append(QPointF(Widget::x,Widget::y));
            qDebug() << this->data;//输出信
            QFile file("data.txt");
            file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append );
            QTextStream out(&file);
            out <<  QString("%3").arg(Widget::x).toUtf8()<< "   " << QString("%1").arg(Widget::y).toUtf8()<<endl;
            file.close();
            this->data_n++;
            QVector<QPointF>olddata=m_serieslist.first()->pointsVector();
            olddata.append(QPointF(Widget::x,Widget::y));
           // olddata.append(QPointF(lastpointtime +olddata.count(), lastpointtime*0.3));//填充数据
                                                                                       //这里添加传入来的数据即可
            axisX->setRange(0, lastpointtime + m_serieslist.first()->count());//设置x坐标轴
            //后期需更改为一开始固定，只有当数据个数超出坐标轴范围时坐标轴开始扩展。
            m_serieslist.first()->replace(olddata);
            lastpointtime++;
        }
    }
}
void chart2::LineFitLeastSquares(float *data_x, float *data_y, int data_n)
{
    float A = 0.0;
    float B = 0.0;
    float C = 0.0;
    float D = 0.0;
    float E = 0.0;
    float F = 0.0;

    for (int i=0; i<data_n; i++)
    {
        A += data_x[i] * data_x[i];
        B += data_x[i];
        C += data_x[i] * data_y[i];
        D += data_y[i];
    }

    // 计算斜率a和截距b
    float a, b, temp = 0;
    if( temp = (data_n*A - B*B) )// 判断分母不为0
    {
        a = (data_n*C - B*D) / temp;
        b = (A*D - B*C) / temp;
    }
    else
    {
        a = 1;
        b = 0;
    }

   qDebug() << "斜率a和截距b分别为：" << a<<"  "<<b;//输出信息
   this->k=a;
   this->b=b;
    // 计算相关系数r
//    float Xmean, Ymean;
//    Xmean = B / data_n;
//    Ymean = D / data_n;

//    float tempSumXX = 0.0, tempSumYY = 0.0;
//    for (int i=0; i<data_n; i++)
//    {
//        tempSumXX += (data_x[i] - Xmean) * (data_x[i] - Xmean);
//        tempSumYY += (data_y[i] - Ymean) * (data_y[i] - Ymean);
//        E += (data_x[i] - Xmean) * (data_y[i] - Ymean);
//    }
//    F = sqrt(tempSumXX) * sqrt(tempSumYY);

//    float r;
//    r = E / F;
}

void chart2::on_pushButton_3_clicked()
{
//    float datax[10]={1,2,3,4,5,6,7,8,9,1};
//    float datay[10]={-0.447,1.978,3.28,6.16,7.08,7.34,7.66,9.56,9.48,9.3};
//    int data_n=10;
    int i;
    float x[data_n-1];
    float y[data_n-1];
    for (i=0;i<this->data_n;i++) {
        x[i]=this->data[i].x();
        y[i]=this->data[i].y();
    }
    //void LineFitLeastSquares(float *data_x, float *data_y, int data_n);
    this->LineFitLeastSquares(x,y,this->data_n-1);
    QString str1 = QString("斜率为 %1").arg(k);//float转化为字符串
    QString str2 = QString("截距为%1").arg(b);//
    ui->label_2->setText(str1);
    ui->label_3->setText(str2);
}

void chart2::on_pushButton_2_clicked()
{
    QList<QPointF> data;
    for(float x = 0; x < Widget::x; x++)
    {
       data.append(QPointF(x, ui->doubleSpinBox->text().toFloat()*x+ui->doubleSpinBox_2->text().toFloat()));
    }
    addSeries(data);
}
