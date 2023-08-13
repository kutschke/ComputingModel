#include "WeekInMonth.hh"
#include "constants.hh"

#include <ostream>

WeekInMonth::WeekInMonth ( PlanWeek const& aweek, unsigned anDays ):
  _week(aweek),
  _nDays(anDays),
  _fraction( double(_nDays)/double(constants::daysPerWeek) ) {
}

std::ostream& operator<<(std::ostream& os, const WeekInMonth& w ){
  /*
  os << "Week:  "    << w.week()
     << "nDays: "    << w.nDays()
     << "fraction: " << w.fraction();
  */
  return os;
}
