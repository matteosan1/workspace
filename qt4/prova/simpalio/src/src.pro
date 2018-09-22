SOURCES += main.cpp \
 barbero.cc \
 cavallo.cc \
 contrada.cc \
 fantino.cc \
 TRandom.cc \
 partito.cc \
 utility.cc
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = ../bin/simpalio

QT -= gui
HEADERS += barbero.h \
cavallo.h \
contrada.h \
fantino.h \
TRandom.h \
partito.h \
main.h \
utility.h
