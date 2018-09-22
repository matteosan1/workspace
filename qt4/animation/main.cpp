 #include <QtGui>

 #include "toplevel.h"

 int main(int argc, char **argv)
 {
     QApplication app(argc, argv);

     qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

     KAstTopLevel topLevel;
     topLevel.setWindowTitle("Ported Asteroids Game");
     topLevel.show();

     app.setQuitOnLastWindowClosed(true);
     return app.exec();
 }
