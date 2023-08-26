#include "RunPeriod.hh"
#include "DurationCalculator.hh"
#include "constants.hh"
#include "dateHelpers.hh"

#include <cmath>
#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;

RunPeriod::RunPeriod( Config const& conf):
  _comment(conf.comment()),
  _liveFraction(conf.liveFraction()),
  _triggerRejection(conf.triggerRejection()),
  _type(RunType( conf.type())),
  _color(Color(conf.color()))
{

  // There is no c'tor from a date in this format!
  _startDate.Set( dayStart(conf.start()).c_str() );
  _endDate.Set(   dayEnd(conf.end()    ).c_str() );

  DurationCalculator dc;
  _nDays = std::round(dc.inDays( _startDate, _endDate));
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
  if ( _weeks.size() < 6 ) {
    for ( auto w: _weeks ){
      os << prefix << w << endl;
    }
  } else{
    size_t n = _weeks.size()-1;
    os << prefix << _weeks.at(0)    << endl;
    os << prefix << _weeks.at(1)    << endl;
    os << prefix << "............"  << endl;
    os << prefix << _weeks.at(n-1)  << endl;
    os << prefix << _weeks.at(n)    << endl;
  }


}
