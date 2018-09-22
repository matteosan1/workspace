###
# MAIN PROJECT FILE
#
# This project includes dependencies building, and can be built
# standalone.

TEMPLATE = subdirs

SUBDIRS = lib_logging \
          lib_clone

lib_logging.file    =   lib_logging.pro
lib_clone.file      =   clone.pro

lib_clone.depends   += lib_logging

OTHER_FILES +=  \
    project.pri \
    clone.pri
