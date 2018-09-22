#include <qwidget.h>

class LED: public QWidget {
    Q_OBJECT
  public:
    LED(QWidget *parent = 0);
  public slots:
    void switchLED();
  protected:
    void paintEvent(QPaintEvent *);
  private:
    bool lit;
    const int width, height;
};

#include <qpalette.h>
#include <qcolor.h>
#include <qpainter.h>
#include <QVBoxLayout>
#include "led.moc"

LED::LED(QWidget *parent):
  QWidget(parent),
  width(28), height(12) {
  setFixedSize(width, height);
  lit = false;
}

void LED::paintEvent(QPaintEvent *) {
  lit ?  setPalette(QPalette(Qt::green)) : setPalette(QPalette(Qt::white));
  QPainter p(this);
  p.drawRect(0, 0, width, height);
}

void LED::switchLED() {
  lit = ! lit;
  repaint();
}

#include <qapplication.h>
#include <qpushbutton.h>
//nclude <qvbox.h>

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QVBoxLayout *box = new QVBoxLayout();
  QWidget *led = new LED(box);
  QPushButton *button = new QPushButton("Click me!", box);
  QObject::connect(button, SIGNAL(clicked()), led, SLOT(switchLED()));
  app.setMainWidget(box);
  box->show();
  return app.exec();
}
