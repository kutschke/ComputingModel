#include "PlanWeek.hh"
#include "constants.hh"
#include "dateHelpers.hh"

#include <iostream>
using std::cout;
using std::endl;

// Note about fractional weeks.
// The inputs are validated to ensure that a plan is at least 3 weeks long.
// This ensures that the first and last week of the plan cannot coincide.
// Therefore the computation of _fraction does not need to take into
// account a 1 week plan with missing days at both ends.
PlanWeek::PlanWeek( TDatime const& t0, TDatime const& planEnd):
  _t0(t0)
{

  // This must not be in the intializerlist or else the DST variables  will overwritten.
  _tend.Set((endOfWeek_with_DST_adjustment(_t0)).Convert());

  // Check that t0 falls on a Sunday; if not this is a short week.
  // This can only happen on the first week of the plan.
  auto day = dayOfWeek(_t0);
  _fraction = double(7.-day)/7.;
  _ndays = 7-day;

  // If week ends after the end of the plan, truncate the week.
  // This can only happen on the last week of the plan.
  if ( _tend.Convert() > planEnd.Convert() ){
    _tend.Set(planEnd.Convert());
    auto dow = dayOfWeek(_tend);
    _fraction = double(dow+1)/7.;
    _ndays = dow+1;
  }

  _duration = _tend.Convert()-_t0.Convert()+1;
  _durationInDays = double(_duration)/double(constants::secondsPerDay);

  /*
  auto dayTest = dayOfWeek(_tend);
  auto hourTest = _tend.GetHour();
  cout << "Week: " <<  _t0.AsString() << "   " << _tend.AsString() << " :  " << dayTest << "   " <<  hourTest << "  : "  << day << " " << _ndays << " : " << _durationInDays
       << " " << _springDST
       << " " << _fallDST
       << endl;
  */
}

// Helper function to adjust a week end date for a DST transition earlier in the week.
TDatime PlanWeek::endOfWeek_with_DST_adjustment( TDatime const& t0 ){

  auto day0 = dayOfWeek(t0);
  // For most weeks, the end of the week is easy to calculate
  TDatime tmp(t0.Convert()+(constants::daysPerWeek-day0)*constants::secondsPerDay-1 );

  // Prep to test for DST transitions.
  auto dayTest = dayOfWeek(tmp);
  auto hourTest = tmp.GetHour();

  // Spring DST shift.
  if ( dayTest != 6 ){
    tmp.Set(tmp.Convert()-constants::secondsPerHour);
    _springDST = true;
  } // Fall DST shift.
  else if ( hourTest == 22 ){
    tmp.Set(tmp.Convert()+constants::secondsPerHour);
    _fallDST = true;
  }

  return tmp;
}

std::ostream& operator<<(std::ostream& os,
                         const PlanWeek& w ){
  os << "Start: " << w.t0().AsString()
     << "  End: " << w.tend().AsString()
    ;

  if ( w.springDST() ){
    os << "  Spring DST: " << w.durationInDays();
  } else if ( w.fallDST() ){
    os << "  Fall DST: "   << w.durationInDays();
  }

  if ( w.nDays() != constants::daysPerWeek ){
    os << "  Short week; number of days: " << w.nDays();
  }

  return os;
}
