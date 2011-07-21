#-------------------------------------------------
#
# Project created by QtCreator 2011-07-20T17:59:18
#
#-------------------------------------------------

QT       += core

QT       -= gui

INCLUDEPATH += /usr/local/include/PacMan
LIBS += -L/usr/lib -lPacMan -lpcap


TARGET = OUILookup
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
