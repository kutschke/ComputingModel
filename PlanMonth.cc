#include "PlanMonth.hh"

#include "constants.hh"
#include "dateHelpers.hh"
#include "DurationCalculator.hh"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// Helper struct
struct YearMonth{
  YearMonth ( unsigned ay, unsigned am): y(ay), m(am){}
  YearMonth ( TDatime const& dt ):y(dt.GetYear()), m(dt.GetMonth()){}

  unsigned y; // Year
  unsigned m; // Month

  bool operator==( const YearMonth& rhs) const{
    return (y == rhs.y && m == rhs.m);
  }

};


PlanMonth::PlanMonth( TDatime const& t0, TDatime const& planEnd, std::vector<PlanWeek>& aweeks):_t0(t0){
  auto month = monthNumber(t0);
  auto year  = t0.GetYear();
  auto _nDays = daysPerMonth( month, year );
  uint32_t end = t0.Convert() + _nDays*constants::secondsPerDay-1;

  // End is at 23:59:59 on the last day of the month.
  _tend.Set(end);

  auto endmonth = monthNumber(_tend);
  auto endhour  = _tend.GetHour();

  // Correct for spring and fall daylight savings transitions
  if ( endmonth > month ){
    _springDST = true;
    _tend.Set(end-constants::secondsPerHour);
  } else if ( endhour == 22){
    _tend.Set(end+constants::secondsPerHour);
    _fallDST = true;
  }

  DurationCalculator dCalc;
  _duration       = dCalc.inSeconds( _t0, _tend);
  _durationInDays = dCalc.inDays( _t0, _tend);

  connectWeeks( aweeks );

  /*
  cout << _t0.AsString() << "   " << _tend.AsString()
       << "    Number of weeks: " << _weeks.size()
       << " " << _durationInDays;
  if  ( _springDST ) {
    cout << "  Spring DST";
  }
  if  ( _fallDST ) {
    cout << "  Fall DST";
  }
  cout << endl;

  for ( auto w : _weeks ){
    cout << "     " << *w << endl;
  }
  */

}

// Update the _weeks data member to point to each week that has
// at least one day that is part of the month.
void PlanMonth::connectWeeks( std::vector<PlanWeek> const& ws ){

  YearMonth ym(_t0);
  for ( auto const& w : ws ){
    YearMonth wt0( w.t0() );
    bool inMonth{false};
    if ( wt0 == ym ){
      inMonth = true;
    } else {
      YearMonth wtend( w.tend() );
      if ( wtend == ym ){
        inMonth = true;
      }
    }
    if ( inMonth ){
      //cout << "    In month: " << w << endl;
      _weeks.emplace_back( &w ); 
    }
  } // end for
}

void PlanMonth::printWeeks ( std::ostream& os, std::string const& prefix ) const{
  for ( auto w: _weeks ){
    os << prefix << *w << endl;
  }
}

std::ostream& operator<<(std::ostream& os, const PlanMonth& pm ){

  os << "Start: "     << pm.t0().AsString()
     << "  End: "     << pm.tend().AsString()
     << "  nWeeks: "  << pm.weeks().size()
    ;

  if ( pm.springDST() ){
    os << "  Spring DST: " << pm.durationInDays();
  } else if ( pm.fallDST() ){
    os << "  Fall DST: "   << pm.durationInDays();
  }

  return os;
}

