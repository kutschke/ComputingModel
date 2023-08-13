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


PlanMonth::PlanMonth( TDatime const& t0, TDatime const& planEnd, std::vector<PlanWeek> const& aweeks):_t0(t0){
  auto month = monthNumber(t0);
  auto year  = t0.GetYear();
  _nDays = daysPerMonth( month, year );
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
  checkWeeks(   aweeks );

}

// Update the _weeks data member to point to each week that has
// at least one day that is part of the month.
void PlanMonth::connectWeeks( std::vector<PlanWeek> const& ws ){

  YearMonth ym(_t0);
  for ( auto const& w : ws ){
    YearMonth wt0( w.t0() );
    YearMonth wtend( w.tend() );
    bool inMonth{false};
    unsigned nDays(0);

    // First (last) week of the plan are constrained to start(end) on a boundary of a
    // calenar quarter and nDays is shortened accordingly.  So these weeks are,
    // by construction, fully contained withn the month.

    if ( wt0 == ym && wtend == ym ){
      // Fully contained within the month.
      inMonth = true;
      nDays=w.nDays();
    } else if ( wt0 == ym ) {
      // This week starts in the month and ends out of the month
      inMonth = true;
      nDays=dayOfWeek(_tend)+1;
    } else if ( wtend == ym ){
      inMonth = true;
      nDays=constants::daysPerWeek-dayOfWeek(_t0);;
    }

    if ( inMonth ){
      _weeksInMonth.emplace_back( w, nDays );
    }

  } // end for
}

// Check that sum of the days in the weeks in this month
// add up to the number of days in the month.
void PlanMonth::checkWeeks( std::vector<PlanWeek> const& ws ){

  unsigned n{0};
  for ( auto const& w : _weeksInMonth ){
    n += w.nDays();
  }
  if ( n != _nDays ){
    cerr << "Sum of days in _weeksInMonth does not match number of days in the month. " << endl;
    cerr << "   Month starting: " << _t0.AsString() << endl;
    cerr << "   Sum of days: " << n <<  "  Days in month: " << _nDays << endl;
    throw std::logic_error("Inconsistent days in the month.");
  }
}


void PlanMonth::printWeeks ( std::ostream& os, std::string const& prefix ) const{
  for ( auto w: _weeksInMonth){
    os << prefix << w.week() << "  Days in this month: " << w.nDays() << "   Fraction: " << w.fraction() << endl;
  }
}

std::ostream& operator<<(std::ostream& os, const PlanMonth& pm ){

  os << "Start: "     << pm.t0().AsString()
     << "  End: "     << pm.tend().AsString()
     << "  nWeeks: "  << pm.weeksInMonth().size()
    ;

  if ( pm.springDST() ){
    os << "  Spring DST: " << pm.durationInDays();
  } else if ( pm.fallDST() ){
    os << "  Fall DST: "   << pm.durationInDays();
  }

  return os;
}

