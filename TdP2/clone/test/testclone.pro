include(../clone.pri)
include(../lib_logging/logging.pri)

### Build

CONFIG -= debug_and_release app_bundle

CONFIG(release, release|debug) {
    BUILD_TYPE = "Release"
    DEFINES += NDEBUG QT_NO_DEBUG_OUTPUT
} else {
    BUILD_TYPE = "Debug"
    CONFIG += warn_on
}
message( *** $$TARGET build: $$BUILD_TYPE)
OUTDIR = "$$OUT_PWD/build/$$BUILD_TYPE"

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS_DEBUG += -O0 -g -ggdb
QMAKE_CXXFLAGS_RELEASE += -O3

OBJECTS_DIR = $$OUTDIR
MOC_DIR = $$OUTDIR
DESTDIR = $$OUTDIR

LIBS += -L$$OUT_PWD/../build/$$BUILD_TYPE

unix:QMAKE_LFLAGS += "-Wl,-rpath,'\$\$ORIGIN'"

### Test

QT = core testlib

CONFIG += console
CONFIG += testcase

INCLUDEPATH += "$$IN_PWD"

HEADERS += "$$IN_PWD"/common/testutils.h
SOURCES += "$$IN_PWD"/common/testutils.cpp

message( *** Test)

# Custom

HEADERS += \
    clonetestsuite.h

SOURCES += \
    clonetestsuite.cpp \
    testclone.cpp
