#include "WeekIn.hh"
#include "constants.hh"

#include "PlanWeek.hh"

#include <ostream>

WeekIn::WeekIn ( PlanWeek const& aweek, unsigned anDays ):
  _week(aweek),
  _nDays(anDays),
  _fractionOfWeek( double(_nDays)/double(constants::daysPerWeek) ) {
}

std::ostream& operator<<(std::ostream& os, const WeekIn& w ){
  os << "WeekIn:  "           << w.week()
     << "  nDays: "          << w.nDays()
     << "  fractionOfWeek: " << w.fractionOfWeek();
  return os;
}
