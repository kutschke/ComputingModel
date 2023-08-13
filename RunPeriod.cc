#include "RunPeriod.hh"
#include "dateHelpers.hh"

#include <iostream>
#include <string>
using std::cerr;
using std::cout;
using std::endl;

RunPeriod::RunPeriod( Config const& conf):
  _comment(conf.comment()),
  _fraction(conf.fraction()),
  _type(RunType( conf.type()))
{
  _startDate.Set( dayStart(conf.start()).c_str() );
  _endDate.Set(   dayEnd(conf.end()    ).c_str() );
}

std::ostream& operator<<(std::ostream& os, const RunPeriod& r ){
  os << "  Type: "     << r.type()
     << "  Start: "    << r.startDate().AsString()
     << "  End: "      << r.endDate().AsString()
     << "  Fraction: " << r.fraction();
  if ( !r.comment().empty() ){
    os << "\n        " << r.comment();
  }
  return os;
}
