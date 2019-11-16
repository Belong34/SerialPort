#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <qDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTime>
#include <QDateTime>
#include "charts.h"
#include "chart2.h"
#include "form.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:
    static float x,y,v;
    static int sendFlag;

private slots:
    void Read_Date();       //读取串口数据
    void find_port();       //查找可用串口
    void sleep(int msec);      //延时函数

    void on_send_button_clicked();
    void on_open_port_clicked();
    void on_close_port_clicked();
    void on_clear_button_1_clicked();
    void on_clear_button2_clicked();
    void on_receive_modl_clicked();
    void on_send_modl_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_send_text_window_textChanged();

private:
    Ui::Widget *ui;
    Charts *chart;
    chart2 *chartCs;
    Form *form;
    QSerialPort *serialport;
    bool textstate_receive;
    bool textstate_send;
};

#endif // WIDGET_H
