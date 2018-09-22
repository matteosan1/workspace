###
# This file is for internal use only

### DETECT COMPILE TYPE
CONFIG(release, release|debug) {
    BUILD_TYPE = Release
} else {
    BUILD_TYPE = Debug
}
message( *** lib_logging include: $$BUILD_TYPE)

### LINK lib_logging
LIBS += -L$$OUT_PWD/build/$$BUILD_TYPE
QMAKE_RPATHDIR += $$OUT_PWD/build/$$BUILD_TYPE

### OVERRIDE BUILD
# Out-of-tree building
BUILD_DIR = $$OUT_PWD/build

### OVERRIDE INSTALL
unix {
    target.path = $$OUT_PWD/bin
    INSTALLS += target
}

include(lib_clone.pri)
