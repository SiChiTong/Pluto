#-------------------------------------------------
#
# Project created by QtCreator 2017-01-27T13:17:48
#
#-------------------------------------------------

QT       += widgets

TARGET = QPlutoTheme
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qplutotheme.cpp

HEADERS += qplutotheme.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
