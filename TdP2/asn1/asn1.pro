include(../version.pri)

TARGET = asn1
DEFINES += LIB_ASN1_LIBRARY

TEMPLATE = lib

INCLUDEPATH += "$$PWD/include"

HEADERS += "$$IN_PWD/include/*.h" \
    "$$IN_PWD/asn1_helper.h" \
    "$$IN_PWD/message_list.h"
SOURCES += "$$IN_PWD/src/*.c"

QT -= gui

### Build
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS_DEBUG += -O0 -g -ggdb
QMAKE_CXXFLAGS_RELEASE += -O3

BUILD_DIR = $$OUT_PWD/../build

unix:QMAKE_LFLAGS += "-Wl,-rpath,'\$\$ORIGIN'"

CONFIG(release, release|debug) {
    BUILD_TYPE = "Release"
    DEFINES += NDEBUG QT_NO_DEBUG_OUTPUT
} else {
    BUILD_TYPE = "Debug"
    CONFIG += warn_on
}
message( *** $$TARGET build: $$BUILD_TYPE)
DESTDIR = "$$BUILD_DIR/$$BUILD_TYPE"
MOC_DIR = $$OUT_PWD/$$BUILD_TYPE/obj
OBJECTS_DIR = $$OUT_PWD/$$BUILD_TYPE/obj

LIBS += -L$$OUT_PWD/../build/$$BUILD_TYPE
QMAKE_RPATHDIR += $$OUT_PWD/../build/$$BUILD_TYPE

# Install
unix {
    target.path = $$OUT_PWD/../bin
    INSTALLS += target
}

OTHER_FILES += \
    README.md \
    asn1.pri \
    *.asn1

DISTFILES += \
    asn1.pri \
    commonmanager.asn1

