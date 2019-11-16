#ifndef CHART2_H
#define CHART2_H

#include <QWidget>
#include <QtCharts/QChart>
#include<QtCharts/QChartView>   //两个基本模块
#include<QPointF>     //点类
#include<QList>         //列表
#include <QtCore/QTimer>   //定时器

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;                 //引入这两个类而免于引入整个头文件的方法
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE   //使用qtchart需要加入这条语句


namespace Ui {
class chart2;
}

class chart2 : public QWidget
{
    Q_OBJECT

public:
    explicit chart2(QWidget *parent = nullptr);
    ~chart2();
    QChartView *m_chartView;   //因为布局时其它函数会访问这个画布，所以设为public
    //virtual ~chart2();
    QList<QPointF> setdata();    //预留这个函数作为一个设置图表数据的接口，将外界数据传给图表

public:
    static QList<QPointF> data;
    static int data_n;

public slots:
//	void handleTimeout();
//几个操作数据的槽函数
    void addSeries(QList<QPointF> &data);     //新增一条曲线
    void removeSeries();                     //移出一条曲线
    void connectMarkers();                   //连接图线与图例
    void disconnectMarkers();               //断开图线与图例
    void handleMarkerClicked();           //占击图例时的处理函数
protected:
    void timerEvent(QTimerEvent *event)Q_DECL_OVERRIDE;  //定时器触发事件，重构
    void LineFitLeastSquares(float *data_x, float *data_y, int data_n);//手写的最小二乘法拟合直线  10.28
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::chart2 *ui;
    QTimer m_timer;     //定时器指针

    QChart * m_chart;     //图表组件，可理解为画笔，用它画曲线
    QList<QSplineSeries *> m_serieslist;   //曲线列表，splineseries为光滑曲线

    QSplineSeries *m_series;     //曲线指针
    QStringList m_titles;             //标题
    QValueAxis *axisX;             //x坐标轴
    QValueAxis *axisY;             //y坐标轴

    qreal m_step;
    qreal m_x;
    qreal m_y;

    //直线拟合的系数
    float k;
    float b;

};

#endif // CHART2_H
