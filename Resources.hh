#ifndef Resources_hh
#define Resources_hh

//
// Resources needed in some time period (week, month, quarter, ... )
//

#include "Data.hh"

#include <map>

struct Resources {
  Resources():index(99999999){}
  Resources( size_t i):index(i){}

  void addRawData( Data const& d );

  size_t                  index;   // Index into the week, month, quarter ...
  std::map<DataType,Data> rawData;
};

#endif
