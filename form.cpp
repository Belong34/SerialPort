#include "form.h"
#include "ui_form.h"
#include "qfile.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    QFile file("data.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
     QByteArray t = file.readAll();
     ui->textEdit->setText(QString(t));
     file.close();
}

Form::~Form()
{
    delete ui;
}
