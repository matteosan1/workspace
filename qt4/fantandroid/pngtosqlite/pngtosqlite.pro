QT += core sql widgets gui

CONFIG += c++11

TARGET = pngtosqlite
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../app/insertgiocatori.cpp \
    ../app/ComboBoxDelegate.cpp \
    ../app/giocatore.cpp \
    ../app/prestazione.cpp \
    customsqlmodel.cpp \
    teamModifier.cpp \
    mainwindow.cpp \
    rulesetter.cpp \
    fixtures.cpp \
    insertlineup.cpp \
    player.cpp

FORMS += \
    rules.ui \
    mainwindow.ui \
    teammodifier.ui \
    cup.ui \
    insertlineups.ui

HEADERS += \
    ../app/insertgiocatori.h \
    ../app/ComboBoxDelegate.h \
    ../app/giocatore.h \
    ../app/prestazione.h \
    customsqlmodel.h \
    teamModifier.h \
    mainwindow.h \
    rulesetter.h \
    fixtures.h \
    insertlineup.h \
    player.h
