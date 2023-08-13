#ifndef PlanMonth_hh
#define PlanMonth_hh

//
// Attributes of one month in the plan.
//

#include "PlanWeek.hh"
#include "WeekInMonth.hh"

#include "TDatime.h"

#include <iosfwd>
#include <string>
#include <vector>

class PlanMonth{

public:

  PlanMonth( TDatime const& t0, TDatime const& planEnd, std::vector<PlanWeek> const& weeks);

  TDatime t0()   const { return _t0;  }
  TDatime tend() const { return _tend;}

  unsigned nDays()          const { return _nDays;     }

  std::vector<WeekInMonth> const& weeksInMonth() const { return _weeksInMonth; }


  unsigned duration()       const { return _duration;  }
  float    durationInDays() const { return _durationInDays; }
  bool     springDST()      const { return _springDST; }
  bool     fallDST()        const { return _fallDST;   }

  void printWeeks ( std::ostream& os, std::string const& prefix ) const;

private:
  TDatime _t0;                     // Date at start of month
  TDatime _tend;                   // Date at end of month
  unsigned _nDays = 0;             // Number of days in this month; corrected for leap years.

  unsigned _duration = 0;          // Duration of the week, in seconds ( DST Transistions are shorter or longer )
  float    _durationInDays = 0;    // _duration in units of floating point days.

  std::vector<WeekInMonth> _weeksInMonth; // Information about the weeks in this month;
                                          // Includes weeks partly in the month.

  bool     _springDST = false;    // This month contains a spring forward daylight savings transition
  bool     _fallDST   = false;    // This month contains a fall back daylight savings transition

  void connectWeeks( std::vector<PlanWeek> const& ws );
  void checkWeeks(   std::vector<PlanWeek> const& ws );

};

std::ostream& operator<<(std::ostream& ost, const PlanMonth& pw );

#endif
