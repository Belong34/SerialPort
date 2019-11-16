#ifndef CHARTS_H
#define CHARTS_H

#include <QMainWindow>
#include <QList>
#include <QtCharts>//在界面头文件包含这两个文件
#include <QTimer>

QT_CHARTS_USE_NAMESPACE//在界面头文件包含这两个文件

namespace Ui {
class Charts;
}

class Charts : public QMainWindow
{
    Q_OBJECT

public:
    explicit Charts(QWidget *parent = nullptr);
    ~Charts();

    QTimer m_timer;
    QChart chart;
    QSplineSeries m_series;
    QStringList m_titles;
    QValueAxis m_axis;
    qreal m_step;
    qreal m_x;
    qreal m_y;
    //QList<float> xList;
    //QList<float> yList;

public slots:
    void creatData();//模拟数据收发绘制散点图
    void RealtimeDataSlot();//曲线数据槽

private:
    Ui::Charts *ui;
};

#endif // CHARTS_H
