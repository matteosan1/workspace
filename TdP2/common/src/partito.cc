#include "partito.h"

namespace common {

Partito::Partito()
{}

void Partito::setPartito(const int& daChi, const TipoPartito& tipo, const int& prezzo)
{
    m_contrada = daChi;
    m_tipo = tipo;
    m_soldi = prezzo;
    m_eseguito = false;
}

Partito::~Partito()
{}

void Partito::setPartito(const int& daChi, const int& controChi, const TipoPartito& tipo, const int& prezzo)
{
    m_contrada = daChi;
    m_contrada2 = controChi;
    m_tipo = tipo;
    m_soldi = prezzo;
    m_eseguito = false;
}
/*
QDataStream& operator<<(QDataStream& out, Partito x) {
  
  out << x.contrada << " ";
  out << x.contrada2 << " ";
  out << x.tipo << " ";
  out << x.soldi << " ";
  out << x.eseguito << "\n";
  
  return out;
}

QTextStream& operator<<(QTextStream& out, Partito x) {
  
  out << x.contrada << " ";
  out << x.contrada2 << " ";
  out << x.tipo << " ";
  out << x.soldi << " ";
  out << x.eseguito << "\n";
  
  return out;
}

QDataStream& operator>>(QDataStream& in, Partito& x) {
  
  int a = (int)x.eseguito;
  in >> x.contrada >> x.contrada2 >> x.tipo >> x.soldi >> a;
  
  return in;
}

QTextStream& operator>>(QTextStream& in, Partito& x) {
  
  int a = (int)x.eseguito;
  in >> x.contrada >> x.contrada2 >> x.tipo >> x.soldi >> a;
  
  return in;
}
*/
} // common
