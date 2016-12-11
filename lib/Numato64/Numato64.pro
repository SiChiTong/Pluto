#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T11:02:33
#
#-------------------------------------------------

QT       -= core serialport

CONFIG += -std=c++0

TARGET = Numato64
TEMPLATE = lib
CONFIG += staticlib

SOURCES += numato64.cpp

HEADERS += numato64.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
