#include "Run.hh"
#include "dateHelpers.hh"

#include <iostream>
#include <string>
using std::cerr;
using std::cout;
using std::endl;

Run::Run(){
}

Run::Run( Config const& conf){
  _type = RunType( conf.type());
  _startDate.Set( dayStart(conf.start()).c_str() );
  _endDate.Set(   dayEnd(conf.end()    ).c_str() );
  _fraction = conf.fraction();
}

std::ostream& operator<<(std::ostream& os, const Run& r ){
  os << "Run type: "   << r.type()
     << "  Start: "    << r.startDate().AsString()
     << "  End: "      << r.endDate().AsString()
     << "  Fraction: " << r.fraction();
  return os;
}
