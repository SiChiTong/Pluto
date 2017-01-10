#-------------------------------------------------
#
# Project created by QtCreator 2017-01-09T20:17:05
#
#-------------------------------------------------

QT       -= core

TARGET = Roboteq
TEMPLATE = lib
CONFIG += staticlib

DEFINES += ROBOTEQ_LIBRARY

SOURCES += roboteq.cpp

HEADERS += roboteq.h\
        roboteq_global.h\
        ErrorCodes.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
