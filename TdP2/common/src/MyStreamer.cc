#include "MyStreamer.h"

// FIXME prevedi giocatori con nomi o cognomi con spazi

MyStreamer::MyStreamer() {}

MyStreamer::~MyStreamer() {}

void MyStreamer::dump() {
   std::cout << "Streamer DUMP: " << std::endl;
   std::cout << "SocketNumber: " << socket_number << std::endl;
   std::cout << "Code: " << code << std::endl;
   for(int i=0; i<intStream.size(); i++) 
     std::cout << intStream[i] << "-" << std::endl;
   std::cout << std::endl;
   for(int i=0; i<intStream.size(); i++) 
     std::cout << intStream[i] << "-" << std::endl;
   std::cout << std::endl;
   for(int i=0; i<stringStream.size(); i++) 
     std::cout << (const char*)stringStream[i].toLatin1() << "-" << std::endl;
   std::cout << std::endl;
}

void MyStreamer::clear() {

    socket_number = -1;
    code = Dummy;
    intStream.clear();
    cavalloStream.clear();
    fantinoStream.clear();
    contradaStream.clear();
    stringListStream.clear();
    stringStream.clear();
    //giocatoreStream;
}

QDataStream& operator<<(QDataStream& out, MyStreamer x) {

    out << x.socket_number;
    out << (int)x.code;
    out << x.intStream;
    out << x.cavalloStream;
    out << x.fantinoStream;
    out << x.contradaStream;
    out << x.stringListStream;
    out << x.stringStream;
    out << x.giocatoreStream;
    out << x.offertaStream;
    out << x.partitoStream;

    return out;
}

QDataStream& operator>>(QDataStream& in, MyStreamer& x) {
  
  int code;
  in >> x.socket_number;
  in >> code;
  x.code = (MessageCode)code;
  in >> x.intStream;
  in >> x.cavalloStream;
  in >> x.fantinoStream;
  in >> x.contradaStream;
  in >> x.stringListStream;
  in >> x.stringStream;
  in >> x.giocatoreStream;
  in >> x.offertaStream;
  in >> x.partitoStream;
  
  return in;
}
