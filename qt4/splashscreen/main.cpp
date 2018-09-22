#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QMainWindow>

int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
     QPixmap pixmap("./splash.jpg");
     QSplashScreen splash(pixmap);
     splash.show();
     splash.showMessage("PiPPo PuPPa", Qt::AlignRight|Qt::AlignTop, Qt::white);
     app.processEvents();
      sleep(4);
     QMainWindow window;
     window.setWindowOpacity(0.5);
     window.show();
     splash.finish(&window);
     return app.exec();
 }

