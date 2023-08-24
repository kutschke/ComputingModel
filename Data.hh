#ifndef Data_hh
#define Data_hh

//
// Information about a quantity of data, either per day, week, month, quarter, aggregate ...
//

#include "DataType.hh"

class Data {
public:

  Data():_type(DataType::unknown),_events(0.),_size(0.){}

  Data ( DataType atype, double aevents, double asize, int anDays);

  DataType type()   const { return _type;}
  double   events() const { return _events;}
  double   size()   const { return _size;}
  int      nDays()  const { return _nDays;}

  Data& operator+=( Data const& rhs);

private:

  DataType _type;
  double   _events;
  double   _size;
  int      _nDays;

};

std::ostream& operator<<(std::ostream& os, const Data& d );

#endif
