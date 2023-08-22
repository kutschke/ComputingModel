#include "Data.hh"

#include <iostream>
#include <stdexcept>

using std::endl;
using std::cerr;
using std::cout;

Data::Data ( DataType atype, double aevents, double asize):
  _type(atype),
  _events(aevents),
  _size(asize){
}

Data& Data::Data::operator+=( Data const& rhs){

  if ( _type != rhs._type ){
    cerr << "Cannot add two Data objects of different type: "
         << "\n  LHS type: " << _type << "   RHS type" << rhs._type << endl;
    throw std::logic_error("Inconsistent arguments to Data operator+= .");
  }

  _events += rhs._events;
  _size   += rhs._size;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Data& d ){
  os << "Data type: " << d.type() << ";  Events:" << d.events() << ";  Size (TB): " << d.size();
  return os;
}
