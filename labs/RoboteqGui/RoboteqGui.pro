#-------------------------------------------------
#
# Project created by QtCreator 2017-01-09T20:35:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoboteqGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h\
            Constants.h

FORMS    += mainwindow.ui


unix:!macx: LIBS += -L$$PWD/../../lib/Roboteq/ -lRoboteq

INCLUDEPATH += $$PWD/../../lib/Roboteq
DEPENDPATH += $$PWD/../../lib/Roboteq

unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib/Roboteq/libRoboteq.a
