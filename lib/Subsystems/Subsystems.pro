#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T21:40:27
#
#-------------------------------------------------

QT       += core serialport

CONFIG += -std=c++0

TARGET = Subsystems
TEMPLATE = lib
CONFIG += staticlib

SOURCES += subsystems.cpp

HEADERS += subsystems.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../Numato64/ -lNumato64

INCLUDEPATH += $$PWD/../Numato64
DEPENDPATH += $$PWD/../Numato64

unix:!macx: PRE_TARGETDEPS += $$PWD/../Numato64/libNumato64.a
