#include "RunPeriod.hh"
#include "constants.hh"
#include "dateHelpers.hh"

#include <iostream>
#include <string>
using std::cerr;
using std::cout;
using std::endl;

RunPeriod::RunPeriod( Config const& conf):
  _comment(conf.comment()),
  _liveFraction(conf.liveFraction()),
  _triggerRejection(conf.triggerRejection()),
  _type(RunType( conf.type()))
{
  _startDate.Set( dayStart(conf.start()).c_str() );
  _endDate.Set(   dayEnd(conf.end()    ).c_str() );
}

void RunPeriod::addWeeks( std::vector<WeekIn> const& ws){
  _weeks.reserve(ws.size());
  for ( auto const& w: ws ){
    _weeks.push_back(w);
  }
}

std::ostream& operator<<(std::ostream& os, const RunPeriod& r ){
  os << "  Type: "              << r.type()
     << "  Start: "             << r.startDate().AsString()
     << "  End: "               << r.endDate().AsString()
     << "  Live fraction: "     << r.liveFraction()
     << "  Trigger rejection: " << r.triggerRejection()
     << "  nWeeks: "            << r.weeks().size();
  if ( !r.comment().empty() ){
    os << "\n        " << r.comment();
  }

  return os;
}

void RunPeriod::printWeeks ( std::ostream& os, std::string const& prefix ) const{
  for ( auto w: _weeks ){
    os << prefix << w << endl; //"  Days in this run period: " << w.nDays() << "   Fraction: " << w.fraction() << endl;
  }
}
