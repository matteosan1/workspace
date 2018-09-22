QT += core
QT -= gui

TARGET = cloneclient
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cloneclient.cpp

HEADERS += \
    cloneclient.h \
    zhelpers.hpp

INCLUDEPATH = /usr/local/include
LIBS += -L/usr/local/lib -lzmq
