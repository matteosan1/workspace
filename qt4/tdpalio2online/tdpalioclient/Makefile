#############################################################################
# Makefile for building: ../bin/tdpalioclient
# Generated by qmake (2.01a) (Qt 4.5.0) on: Thu Jun 25 15:55:27 2009
# Project:  tdpalioclient.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -unix -o Makefile tdpalioclient.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -ltdpaliocommon -lQtGui -lQtNetwork -lQtCore -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = CaricaGiocoDialog.cpp \
		ListaCavalli.cpp \
		ListaCuffie.cpp \
		ListaFantini.cpp \
		ListaVittorie.cpp \
		main.cpp \
		nuovogiocatore.cpp \
		ServerConnectionDialog.cpp \
		tdpalioclient.cpp \
		TrattaDialog.cpp \
		SceltaFantino.cpp \
		Profilo.cpp moc_CaricaGiocoDialog.cpp \
		moc_ListaCavalli.cpp \
		moc_ListaCuffie.cpp \
		moc_ListaFantini.cpp \
		moc_ListaVittorie.cpp \
		moc_nuovogiocatore.cpp \
		moc_ServerConnectionDialog.cpp \
		moc_tdpalioclient.cpp \
		moc_TrattaDialog.cpp \
		moc_SceltaFantino.cpp \
		moc_Profilo.cpp \
		qrc_resource.cpp
OBJECTS       = CaricaGiocoDialog.o \
		ListaCavalli.o \
		ListaCuffie.o \
		ListaFantini.o \
		ListaVittorie.o \
		main.o \
		nuovogiocatore.o \
		ServerConnectionDialog.o \
		tdpalioclient.o \
		TrattaDialog.o \
		SceltaFantino.o \
		Profilo.o \
		moc_CaricaGiocoDialog.o \
		moc_ListaCavalli.o \
		moc_ListaCuffie.o \
		moc_ListaFantini.o \
		moc_ListaVittorie.o \
		moc_nuovogiocatore.o \
		moc_ServerConnectionDialog.o \
		moc_tdpalioclient.o \
		moc_TrattaDialog.o \
		moc_SceltaFantino.o \
		moc_Profilo.o \
		qrc_resource.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		tdpalioclient.pro
QMAKE_TARGET  = tdpalioclient
DESTDIR       = ../bin/
TARGET        = ../bin/tdpalioclient

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_caricagioco.h ui_listagenerica.h ui_listatratta.h ui_nuovogiocatore.h ui_serverconnection.h ui_tdpalio.h ui_tratta.h ui_profilo.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) ../bin/ || $(MKDIR) ../bin/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: tdpalioclient.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtNetwork.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile tdpalioclient.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtNetwork.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile tdpalioclient.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/tdpalioclient1.0.0 || $(MKDIR) .tmp/tdpalioclient1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/tdpalioclient1.0.0/ && $(COPY_FILE) --parents CaricaGiocoDialog.h ListaCavalli.h ListaCuffie.h ListaFantini.h ListaVittorie.h nuovogiocatore.h ServerConnectionDialog.h tdpalioclient.h TrattaDialog.h SceltaFantino.h Profilo.h .tmp/tdpalioclient1.0.0/ && $(COPY_FILE) --parents resource.qrc .tmp/tdpalioclient1.0.0/ && $(COPY_FILE) --parents CaricaGiocoDialog.cpp ListaCavalli.cpp ListaCuffie.cpp ListaFantini.cpp ListaVittorie.cpp main.cpp nuovogiocatore.cpp ServerConnectionDialog.cpp tdpalioclient.cpp TrattaDialog.cpp SceltaFantino.cpp Profilo.cpp .tmp/tdpalioclient1.0.0/ && $(COPY_FILE) --parents caricagioco.ui listagenerica.ui listatratta.ui nuovogiocatore.ui serverconnection.ui tdpalio.ui tratta.ui profilo.ui .tmp/tdpalioclient1.0.0/ && (cd `dirname .tmp/tdpalioclient1.0.0` && $(TAR) tdpalioclient1.0.0.tar tdpalioclient1.0.0 && $(COMPRESS) tdpalioclient1.0.0.tar) && $(MOVE) `dirname .tmp/tdpalioclient1.0.0`/tdpalioclient1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/tdpalioclient1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_CaricaGiocoDialog.cpp moc_ListaCavalli.cpp moc_ListaCuffie.cpp moc_ListaFantini.cpp moc_ListaVittorie.cpp moc_nuovogiocatore.cpp moc_ServerConnectionDialog.cpp moc_tdpalioclient.cpp moc_TrattaDialog.cpp moc_SceltaFantino.cpp moc_Profilo.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_CaricaGiocoDialog.cpp moc_ListaCavalli.cpp moc_ListaCuffie.cpp moc_ListaFantini.cpp moc_ListaVittorie.cpp moc_nuovogiocatore.cpp moc_ServerConnectionDialog.cpp moc_tdpalioclient.cpp moc_TrattaDialog.cpp moc_SceltaFantino.cpp moc_Profilo.cpp
moc_CaricaGiocoDialog.cpp: ui_caricagioco.h \
		CaricaGiocoDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) CaricaGiocoDialog.h -o moc_CaricaGiocoDialog.cpp

moc_ListaCavalli.cpp: ui_listatratta.h \
		ListaCavalli.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ListaCavalli.h -o moc_ListaCavalli.cpp

moc_ListaCuffie.cpp: ui_listagenerica.h \
		../tdpaliocommon/contrada.h \
		ListaCuffie.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ListaCuffie.h -o moc_ListaCuffie.cpp

moc_ListaFantini.cpp: ui_listagenerica.h \
		../tdpaliocommon/fantino.h \
		ListaFantini.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ListaFantini.h -o moc_ListaFantini.cpp

moc_ListaVittorie.cpp: ui_listagenerica.h \
		../tdpaliocommon/contrada.h \
		ListaVittorie.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ListaVittorie.h -o moc_ListaVittorie.cpp

moc_nuovogiocatore.cpp: ui_nuovogiocatore.h \
		../tdpaliocommon/giocatore.h \
		nuovogiocatore.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) nuovogiocatore.h -o moc_nuovogiocatore.cpp

moc_ServerConnectionDialog.cpp: ui_serverconnection.h \
		ServerConnectionDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ServerConnectionDialog.h -o moc_ServerConnectionDialog.cpp

moc_tdpalioclient.cpp: ui_tdpalio.h \
		../tdpaliocommon/giocatore.h \
		../tdpaliocommon/cavallo.h \
		../tdpaliocommon/code.h \
		../tdpaliocommon/MyStreamer.h \
		../tdpaliocommon/contrada.h \
		../tdpaliocommon/fantino.h \
		../tdpaliocommon/partito.h \
		tdpalioclient.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) tdpalioclient.h -o moc_tdpalioclient.cpp

moc_TrattaDialog.cpp: ui_tratta.h \
		../tdpaliocommon/cavallo.h \
		TrattaDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) TrattaDialog.h -o moc_TrattaDialog.cpp

moc_SceltaFantino.cpp: ui_tratta.h \
		../tdpaliocommon/fantino.h \
		SceltaFantino.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) SceltaFantino.h -o moc_SceltaFantino.cpp

moc_Profilo.cpp: ui_profilo.h \
		Profilo.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Profilo.h -o moc_Profilo.cpp

compiler_rcc_make_all: qrc_resource.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resource.cpp
qrc_resource.cpp: resource.qrc \
		pictures/tabellone_10.png \
		pictures/tabellone_bruco.png \
		pictures/tabellone_6.png \
		pictures/tabellone_lupa.png \
		pictures/tabellone_oca.png \
		pictures/tabellone_aquila.png \
		pictures/tabellone_civetta.png \
		pictures/tabellone.jpg \
		pictures/tabellone_11.png \
		pictures/tabellone_9.png \
		pictures/tabellone_istrice.png \
		pictures/tabellone_2.png \
		pictures/tabellone_12.png \
		pictures/tabellone_5.png \
		pictures/tabellone_13.png \
		pictures/tabellone_7.png \
		pictures/tabellone_montone.png \
		pictures/tabellone_giraffa.png \
		pictures/tabellone_16.png \
		pictures/tabellone_14.png \
		pictures/tabellone_20.png \
		pictures/tabellone_17.png \
		pictures/tabellone_torre.png \
		pictures/tabellone_pantera.png \
		pictures/tabellone_3.png \
		pictures/tabellone_8.png \
		pictures/tabellone_15.png \
		pictures/tabellone_drago.png \
		pictures/tabellone_21.png \
		pictures/tabellone_18.png \
		pictures/tabellone_onda.png \
		pictures/tabellone_nicchio.png \
		pictures/tabellone_chiocciola.png \
		pictures/tabellone_4.png \
		pictures/tabellone_selva.png \
		pictures/tabellone_19.png \
		pictures/tabellone_tartuca.png \
		pictures/tabellone_1.png \
		pictures/tabellone_leocorno.png \
		pictures/Tartuca_1.gif \
		pictures/Lupa_1.gif \
		pictures/Giraffa_1.gif \
		pictures/Torre_1.gif \
		pictures/Onda_1.gif \
		pictures/Pantera_1.gif \
		pictures/Selva_1.gif \
		pictures/palazzo_comunale.jpg \
		pictures/Chiocciola_1.gif \
		pictures/Oca_1.gif \
		pictures/Montone_1.gif \
		pictures/Leocorno_1.gif \
		pictures/Nicchio_1.gif \
		pictures/Bruco_1.gif \
		pictures/Civetta_1.gif \
		pictures/Drago_1.gif \
		pictures/Istrice_1.gif \
		pictures/Aquila_1.gif \
		pictures/avanti.png \
		pictures/connect_no.png \
		pictures/history.png \
		pictures/filenew.png \
		pictures/buono.bmp \
		pictures/suff.bmp \
		pictures/killer.png \
		pictures/scarso.bmp
	/usr/bin/rcc -name resource resource.qrc -o qrc_resource.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_caricagioco.h ui_listagenerica.h ui_listatratta.h ui_nuovogiocatore.h ui_serverconnection.h ui_tdpalio.h ui_tratta.h ui_profilo.h
compiler_uic_clean:
	-$(DEL_FILE) ui_caricagioco.h ui_listagenerica.h ui_listatratta.h ui_nuovogiocatore.h ui_serverconnection.h ui_tdpalio.h ui_tratta.h ui_profilo.h
ui_caricagioco.h: caricagioco.ui
	/usr/bin/uic-qt4 caricagioco.ui -o ui_caricagioco.h

ui_listagenerica.h: listagenerica.ui
	/usr/bin/uic-qt4 listagenerica.ui -o ui_listagenerica.h

ui_listatratta.h: listatratta.ui
	/usr/bin/uic-qt4 listatratta.ui -o ui_listatratta.h

ui_nuovogiocatore.h: nuovogiocatore.ui \
		../tdpaliocommon/giocatore.h
	/usr/bin/uic-qt4 nuovogiocatore.ui -o ui_nuovogiocatore.h

ui_serverconnection.h: serverconnection.ui
	/usr/bin/uic-qt4 serverconnection.ui -o ui_serverconnection.h

ui_tdpalio.h: tdpalio.ui
	/usr/bin/uic-qt4 tdpalio.ui -o ui_tdpalio.h

ui_tratta.h: tratta.ui
	/usr/bin/uic-qt4 tratta.ui -o ui_tratta.h

ui_profilo.h: profilo.ui
	/usr/bin/uic-qt4 profilo.ui -o ui_profilo.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

CaricaGiocoDialog.o: CaricaGiocoDialog.cpp CaricaGiocoDialog.h \
		ui_caricagioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CaricaGiocoDialog.o CaricaGiocoDialog.cpp

ListaCavalli.o: ListaCavalli.cpp ListaCavalli.h \
		ui_listatratta.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ListaCavalli.o ListaCavalli.cpp

ListaCuffie.o: ListaCuffie.cpp ListaCuffie.h \
		ui_listagenerica.h \
		../tdpaliocommon/contrada.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ListaCuffie.o ListaCuffie.cpp

ListaFantini.o: ListaFantini.cpp ListaFantini.h \
		ui_listagenerica.h \
		../tdpaliocommon/fantino.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ListaFantini.o ListaFantini.cpp

ListaVittorie.o: ListaVittorie.cpp ListaVittorie.h \
		ui_listagenerica.h \
		../tdpaliocommon/contrada.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ListaVittorie.o ListaVittorie.cpp

main.o: main.cpp tdpalioclient.h \
		ui_tdpalio.h \
		../tdpaliocommon/giocatore.h \
		../tdpaliocommon/cavallo.h \
		../tdpaliocommon/code.h \
		../tdpaliocommon/MyStreamer.h \
		../tdpaliocommon/contrada.h \
		../tdpaliocommon/fantino.h \
		../tdpaliocommon/partito.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

nuovogiocatore.o: nuovogiocatore.cpp nuovogiocatore.h \
		ui_nuovogiocatore.h \
		../tdpaliocommon/giocatore.h \
		../tdpaliocommon/TRandom.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o nuovogiocatore.o nuovogiocatore.cpp

ServerConnectionDialog.o: ServerConnectionDialog.cpp ServerConnectionDialog.h \
		ui_serverconnection.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ServerConnectionDialog.o ServerConnectionDialog.cpp

tdpalioclient.o: tdpalioclient.cpp tdpalioclient.h \
		ui_tdpalio.h \
		../tdpaliocommon/giocatore.h \
		../tdpaliocommon/cavallo.h \
		../tdpaliocommon/code.h \
		../tdpaliocommon/MyStreamer.h \
		../tdpaliocommon/contrada.h \
		../tdpaliocommon/fantino.h \
		../tdpaliocommon/partito.h \
		nuovogiocatore.h \
		ui_nuovogiocatore.h \
		CaricaGiocoDialog.h \
		ui_caricagioco.h \
		ServerConnectionDialog.h \
		ui_serverconnection.h \
		TrattaDialog.h \
		ui_tratta.h \
		SceltaFantino.h \
		Profilo.h \
		ui_profilo.h \
		ListaVittorie.h \
		ui_listagenerica.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tdpalioclient.o tdpalioclient.cpp

TrattaDialog.o: TrattaDialog.cpp TrattaDialog.h \
		ui_tratta.h \
		../tdpaliocommon/cavallo.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TrattaDialog.o TrattaDialog.cpp

SceltaFantino.o: SceltaFantino.cpp SceltaFantino.h \
		ui_tratta.h \
		../tdpaliocommon/fantino.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SceltaFantino.o SceltaFantino.cpp

Profilo.o: Profilo.cpp Profilo.h \
		ui_profilo.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Profilo.o Profilo.cpp

moc_CaricaGiocoDialog.o: moc_CaricaGiocoDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_CaricaGiocoDialog.o moc_CaricaGiocoDialog.cpp

moc_ListaCavalli.o: moc_ListaCavalli.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ListaCavalli.o moc_ListaCavalli.cpp

moc_ListaCuffie.o: moc_ListaCuffie.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ListaCuffie.o moc_ListaCuffie.cpp

moc_ListaFantini.o: moc_ListaFantini.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ListaFantini.o moc_ListaFantini.cpp

moc_ListaVittorie.o: moc_ListaVittorie.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ListaVittorie.o moc_ListaVittorie.cpp

moc_nuovogiocatore.o: moc_nuovogiocatore.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_nuovogiocatore.o moc_nuovogiocatore.cpp

moc_ServerConnectionDialog.o: moc_ServerConnectionDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ServerConnectionDialog.o moc_ServerConnectionDialog.cpp

moc_tdpalioclient.o: moc_tdpalioclient.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_tdpalioclient.o moc_tdpalioclient.cpp

moc_TrattaDialog.o: moc_TrattaDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_TrattaDialog.o moc_TrattaDialog.cpp

moc_SceltaFantino.o: moc_SceltaFantino.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_SceltaFantino.o moc_SceltaFantino.cpp

moc_Profilo.o: moc_Profilo.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Profilo.o moc_Profilo.cpp

qrc_resource.o: qrc_resource.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_resource.o qrc_resource.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

