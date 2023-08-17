#include "Resources.hh"

#include <iostream>
#include <stdexcept>
using std::cout;
using std::cerr;
using std::endl;

void Resources::addRawData( Data const& d ){
  if ( d.type() == DataType::unknown ){
    throw std::logic_error("DataType::unknown not permitted in Resources::addRawData.");
  }
  auto i = rawData.find( d.type() );
  if ( i == rawData.end() ){
    rawData[d.type()] = d;
  } else {
    // This can happend when a run period boundary occurs mid week.
    // Perhaps shifting from commissioning to run fulling of the same time.
    rawData[d.type()] += d;
  }
}
