#include "Data.hh"

#include <iostream>
#include <stdexcept>

using std::endl;
using std::cerr;
using std::cout;

Data::Data ( DataType atype, double aevents, double asize, int anDays):
  _type(atype),
  _events(aevents),
  _size(asize),
  _nDays(anDays){
}

Data::Data ( DataType::enum_type atype, double aevents, double asize, int anDays):
  Data( DataType(atype), aevents, asize, anDays){
}

Data& Data::Data::operator+=( Data const& rhs){

  if ( _type != rhs._type ){
    cerr << "Cannot add two Data objects of different type: "
         << "\n  LHS type: " << _type << "   RHS type" << rhs._type << endl;
    throw std::logic_error("Inconsistent arguments to Data operator+= .");
  }

  _events += rhs._events;
  _size   += rhs._size;
  _nDays  += rhs._nDays;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Data& d ){
  os << "Data type: "    << d.type()
     << ";  Events: "    << d.events()
     << ";  Size (TB): " << d.size()
     << ";  nDays: "     << d.nDays()
    ;
  return os;
}
