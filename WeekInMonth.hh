#ifndef WeekInMonth_hh
#define WeekInMonth_hh

class PlanWeek;

#include <iosfwd>

class WeekInMonth {
public:
  WeekInMonth ( PlanWeek const* aweek, unsigned anDays );

  PlanWeek const& week()     const { return *_week; }
  unsigned        nDays()    const { return _nDays; }
  double          fraction() const { return _fraction; }

private:
  PlanWeek const* _week;
  unsigned        _nDays;
  double          _fraction;
};

std::ostream& operator<<(std::ostream& ost, const WeekInMonth& pw );

#endif
