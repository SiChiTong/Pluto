#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T23:38:04
#
#-------------------------------------------------

QT       -= core serialport

CONFIG += -std=c++0

TARGET = Numato4Relay
TEMPLATE = lib
CONFIG += staticlib

SOURCES += numato4relay.cpp

HEADERS += numato4relay.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
