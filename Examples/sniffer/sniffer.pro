#-------------------------------------------------
#
# Project created by QtCreator 2011-07-28T15:32:59
#
#-------------------------------------------------

QT       += core

QT       -= gui

INCLUDEPATH += /usr/local/include/PacMan
LIBS += -L/usr/lib -lPacMan -lpcap


TARGET = sniffer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../common/commandLineParser.cpp

HEADERS += \
    ../common/commandLineParser.h


