#-------------------------------------------------
#201
# Project created by QtCreator 2019
#说明 chart2封装了一个作图类
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = SerialPort
TARGET = seriertry
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
    form.cpp \
    widget.cpp \
    chart2.cpp

HEADERS  += widget.h \
    chart2.h \
    form.h

FORMS    += widget.ui \
    chart2.ui \
    form.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
