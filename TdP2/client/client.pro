TARGET = client

DEFINES += CLIENT_BASE_LIBRARY

INCLUDEPATH += $$PWD/include

LIBS += -L$$OUT_PWD/../../build/$$BUILD_TYPE
QMAKE_RPATHDIR += $$OUT_PWD/../../build/$$BUILD_TYPE


HEADERS += include/CaricaGiocoDialog.h \
           include/ListaCavalli.h \
           include/ListaCuffie.h \
           include/ListaFantini.h \
           include/ListaVittorie.h \
           include/nuovogiocatore.h \
           include/ServerConnectionDialog.h \
           include/client.h \
           include/TrattaDialog.h \
	   include/SceltaFantino.h \
	   include/Profilo.h

SOURCES += src/CaricaGiocoDialog.cpp \
           src/ListaCavalli.cpp \
           src/ListaCuffie.cpp \
           src/ListaFantini.cpp \
           src/ListaVittorie.cpp \
           src/main.cpp \
           src/nuovogiocatore.cpp \
           src/ServerConnectionDialog.cpp \
           src/client.cpp \
           src/TrattaDialog.cpp \
	   src/SceltaFantino.cpp \
	   src/Profilo.cpp 

FORMS += ui/caricagioco.ui \
         ui/listagenerica.ui \
         ui/listatratta.ui \
         ui/nuovogiocatore.ui \
         ui/serverconnection.ui \
         ui/tdpalio.ui \
         ui/tratta.ui \
         ui/profilo.ui
         
RESOURCES += resource.qrc

DISTFILES += \
client.pri

OTHER_FILES += \
client.pri 

VERSION = 1.0.0
