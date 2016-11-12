#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T21:58:17
#
#-------------------------------------------------

QT       += core gui

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
