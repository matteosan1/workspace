#############################################################################
# Makefile for building: tutorial1
# Generated by qmake (1.07a) (Qt 3.3.6) on: Sat Nov 18 20:09:50 2006
# Project:  tutorial1.pro
# Template: app
# Command: $(QMAKE) -o Makefile tutorial1.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -O2 -D_REENTRANT  -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -DQT_SHARED -DQT_TABLET_SUPPORT
CXXFLAGS = -pipe -Wall -W -O2 -D_REENTRANT  -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -DQT_SHARED -DQT_TABLET_SUPPORT
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I/usr/share/qt3/mkspecs/default -I. -I. -I/usr/include/qt3
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L/usr/share/qt3/lib -L/usr/X11R6/lib -lqt-mt -lXext -lX11 -lm -lpthread
AR       = ar cqs
RANLIB   = 
MOC      = /usr/share/qt3/bin/moc
UIC      = /usr/share/qt3/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = ./

####### Files

HEADERS = cannon.h \
		lcdrange.h
SOURCES = cannon.cpp \
		lcdrange.cpp \
		main.cpp
OBJECTS = cannon.o \
		lcdrange.o \
		main.o
FORMS = 
UICDECLS = 
UICIMPLS = 
SRCMOC   = moc_cannon.cpp \
		moc_lcdrange.cpp
OBJMOC = moc_cannon.o \
		moc_lcdrange.o
DIST	   = tutorial1.pro
QMAKE_TARGET = tutorial1
DESTDIR  = 
TARGET   = tutorial1

first: all
####### Implicit rules

.SUFFIXES: .c .o .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(OBJCOMP) $(LIBS)

mocables: $(SRCMOC)
uicables: $(UICDECLS) $(UICIMPLS)

$(MOC): 
	( cd $(QTDIR)/src/moc && $(MAKE) )

Makefile: tutorial1.pro  /usr/share/qt3/mkspecs/default/qmake.conf /usr/share/qt3/lib/libqt-mt.prl
	$(QMAKE) -o Makefile tutorial1.pro
qmake: 
	@$(QMAKE) -o Makefile tutorial1.pro

dist: 
	@mkdir -p .tmp/tutorial1 && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/tutorial1/ && ( cd `dirname .tmp/tutorial1` && $(TAR) tutorial1.tar tutorial1 && $(GZIP) tutorial1.tar ) && $(MOVE) `dirname .tmp/tutorial1`/tutorial1.tar.gz . && $(DEL_FILE) -r .tmp/tutorial1

mocclean:
	-$(DEL_FILE) $(OBJMOC)
	-$(DEL_FILE) $(SRCMOC)

uiclean:

yaccclean:
lexclean:
clean: mocclean
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET)


FORCE:

####### Compile

cannon.o: cannon.cpp cannon.h

lcdrange.o: lcdrange.cpp lcdrange.h

main.o: main.cpp lcdrange.h \
		cannon.h

moc_cannon.o: moc_cannon.cpp  cannon.h 

moc_lcdrange.o: moc_lcdrange.cpp  lcdrange.h 

moc_cannon.cpp: $(MOC) cannon.h
	$(MOC) cannon.h -o moc_cannon.cpp

moc_lcdrange.cpp: $(MOC) lcdrange.h
	$(MOC) lcdrange.h -o moc_lcdrange.cpp

####### Install

install:  

uninstall:  

