###########################################
# Main project definitions
#
# This file is included by the default .pro file (through the clone.pro)
#
# This file must be included by custom .pro file, i.e. when using this
# library as submodule. The user can override BUILD_DIR and target.path.

include(version.pri)
include(lib_logging/logging.pri)

TARGET = clone

QT += core

TEMPLATE = lib

DEFINES += CLONE_LIBRARY

### BUILD

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS_DEBUG += -O0 -g -ggdb
QMAKE_CXXFLAGS_RELEASE += -O3

# Out-of-tree building
equals(BUILD_DIR, "") {
    BUILD_DIR = $$OUT_PWD/build
    message("$$TARGET using default build dir")
}
else {
    message("$$TARGET using custom build dir: $$BUILD_DIR")
}

CONFIG -= debug_and_release app_bundle

CONFIG(release, release|debug) {
    BUILD_TYPE = Release
    DEFINES += NDEBUG QT_NO_DEBUG_OUTPUT
} else {
    BUILD_TYPE = Debug
    CONFIG += warn_on
}
message( *** $$TARGET build: Release)
DESTDIR = $$BUILD_DIR/$$BUILD_TYPE
MOC_DIR = $$BUILD_DIR/obj/$$BUILD_TYPE/$$TARGET
OBJECTS_DIR = $$BUILD_DIR/obj/$$BUILD_TYPE/$$TARGET

INCLUDEPATH += $$PWD/include
VPATH += $$PWD/include

### FILES

HEADERS += \
    $$PWD/include/lib_clone_global.h  \
    $$PWD/include/clonebackend.h      \
    $$PWD/include/clonebrokeragent.h  \
    $$PWD/include/clonebrokerapp.h    \
    $$PWD/include/clonefrontend.h     \
    $$PWD/include/clonenodeagent.h    \
    $$PWD/include/clonenodeapp.h      \
    $$PWD/include/clonetopic.h        \
    $$PWD/include/zmqhelper.h         \
    $$PWD/include/utilsclone.h

SOURCES +=              \
    $$PWD/src/clonebackend.cpp    \
    $$PWD/src/clonebrokeragent.cpp\
    $$PWD/src/clonebrokerapp.cpp  \
    $$PWD/src/clonefrontend.cpp   \
    $$PWD/src/clonenodeagent.cpp  \
    $$PWD/src/clonenodeapp.cpp    \
    $$PWD/src/zmqhelper.cpp       \
    $$PWD/src/utilsclone.cpp

### INSTALL

equals(target.path, "") {
    unix {
        target.path = /usr/lib
        INSTALLS += target
    }
    message("$$TARGET using default target path")
}
else {
     message("$$TARGET using custom target path: $$target.path")
}

## OTHER

OTHER_FILES +=      \
    clone.pri       \
    lib_logging.pro \
    lib_clone.pro   \
    version_generator.py

