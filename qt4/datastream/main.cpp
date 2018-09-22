#include <QByteArray>
#include <QFile>
#include <QDataStream>
#include <QString>
#include <iostream>

int main(int argc, char *argv[]) {

  int a = 10, b;
  QString s("Matteo"), s1;
  std::cout << a << std::endl;
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_0);
  out << s;
  out << a;

  QFile file("./prova.dat");
  file.open(QIODevice::WriteOnly);
  file.write(block);
  file.close();


  QFile file1("./prova.dat");
  file1.open(QIODevice::ReadOnly);
  QDataStream in(&file1);
  in.setVersion(QDataStream::Qt_4_0);
  in >> s1;
  in >> b;
  file1.close(); 

  std::cout << (const char*)s1.toLatin1() << std::endl;
  std::cout << b << std::endl; 
}
