######################################################################
# Automatically generated by qmake (2.01a) Sat Jul 19 15:12:37 2008
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
QT += network
LIBS += -ltdpaliocommon
DESTDIR = ../bin

# Input
HEADERS += CaricaGiocoDialog.h \
           ListaCavalli.h \
           ListaCuffie.h \
           ListaFantini.h \
           ListaVittorie.h \
           nuovogiocatore.h \
           ServerConnectionDialog.h \
           tdpalioclient.h \
           TrattaDialog.h \
	   SceltaFantino.h \
	   Profilo.h
FORMS += caricagioco.ui \
         listagenerica.ui \
         listatratta.ui \
         nuovogiocatore.ui \
         serverconnection.ui \
         tdpalio.ui \
         tratta.ui \
         profilo.ui
SOURCES += CaricaGiocoDialog.cpp \
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
	   Profilo.cpp 
RESOURCES += resource.qrc
