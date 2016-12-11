QT       += core gui serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += -std=c++0

TARGET = PlutoApp
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../../lib/Subsystems/ -lSubsystems

INCLUDEPATH += $$PWD/../../lib/Subsystems
DEPENDPATH += $$PWD/../../lib/Subsystems

unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib/Subsystems/libSubsystems.a

unix:!macx: LIBS += -L$$PWD/../../lib/Numato64/ -lNumato64

INCLUDEPATH += $$PWD/../../lib/Numato64
DEPENDPATH += $$PWD/../../lib/Numato64

unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib/Numato64/libNumato64.a
