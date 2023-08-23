#ifndef WeekIn_hh
#define WeekIn_hh
//
// A week that is fully or partly contained within a longer time interval, such as a month or a run period.
//

class PlanWeek;

#include <iosfwd>

class WeekIn {
public:
  WeekIn ( PlanWeek const& aweek, unsigned anDays );

  PlanWeek const& week()           const { return _week;           }
  unsigned        nDays()          const { return _nDays;          }
  double          fractionOfWeek() const { return _fractionOfWeek; }

private:
  PlanWeek const& _week;
  unsigned        _nDays;          // Number of days in this week that are part of the longer time period.
  double          _fractionOfWeek; // Fraction of the week in the longer time period.
};

std::ostream& operator<<(std::ostream& os, const WeekIn& w );

#endif
