QT += core
QT -= gui

CONFIG += c++11

TARGET = zmqtest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mysocket.cpp

HEADERS += \
    mysocket.h

INCLUDEPATH += \
    /usr/local/include

LIBS += \
    -L/usr/local/lib

LIBS += -lzmq
