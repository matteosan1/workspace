#-------------------------------------------------
#
# Project created by QtCreator 2016-08-10T14:17:49
#
#-------------------------------------------------

QT += widgets network

TARGET = core
TEMPLATE = lib

DEFINES += CORE_LIBRARY

SOURCES += giocatore.cpp \
           partita.cpp \
           prestazione.cpp \
           punteggi.cpp \
           insertgiocatori.cpp \
           ComboBoxDelegate.cpp

HEADERS += giocatore.h\
           partita.h \
           prestazione.h \
           punteggi.h \
           insertgiocatori.h \
           ComboBoxDelegate.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
