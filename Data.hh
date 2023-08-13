#ifndef Data_hh
#define Data_hh

#include "DataType.hh"

class Data {
public:

  Data ( DataType atype, double events, double asize);

  DataType type()   const { return _type;}
  double   events() const { return _events;}
  double   size()   const { return _size;}

private:

  DataType _type;
  double   _events;
  double   _size;

};

std::ostream& operator<<(std::ostream& os, const Data& d );

#endif
