#-------------------------------------------------
#
# Project created by QtCreator 2011-07-07T01:42:14
#
#-------------------------------------------------

QT       += core

QT       -= gui

INCLUDEPATH += /usr/local/include/PacMan
LIBS += -L/usr/lib -lPacMan -lpcap

TARGET = ArpScanner
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    commandLineParser.cpp

HEADERS += \
    commandLineParser.h
