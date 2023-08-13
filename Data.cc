#include "Data.hh"

Data::Data ( DataType atype, double aevents, double asize):
  _type(atype),
  _events(aevents),
  _size(asize){
}

std::ostream& operator<<(std::ostream& os, const Data& d ){
  return os;
}
