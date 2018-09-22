
TARGET = common

DEFINES += COMMON_BASE_LIBRARY

INCLUDEPATH += $$PWD/include

LIBS += -L$$OUT_PWD/../../build/$$BUILD_TYPE
QMAKE_RPATHDIR += $$OUT_PWD/../../build/$$BUILD_TYPE


# Input
HEADERS += include/barbero.h \
           include/cavallo.h \
           include/code.h \
           include/contrada.h \
           include/fantino.h \
           include/giocatore.h \
           include/partito.h \
           include/TRandom.h \
           include/utility.h

SOURCES += src/barbero.cc \
           src/cavallo.cc \
           src/contrada.cc \
           src/fantino.cc \
           src/giocatore.cc \
           src/partito.cc \
           src/TRandom.cc \
           src/utility.cc

DISTFILES += \
    common.pri

OTHER_FILES += \
    common.pri \
    README.md

VERSION = 1.0.0
