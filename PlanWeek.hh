#ifndef PlanWeek_hh
#define PlanWeek_hh

#include "Data.hh"

#include "TDatime.h"

#include <iosfwd>

class PlanWeek{

public:

  PlanWeek( TDatime const& t0, TDatime const& planEnd);

  TDatime t0()   const { return _t0;  }
  TDatime tend() const { return _tend;}

  std::map<DataType,Data> const& data() const { return _data;}

  unsigned nDays()          const { return _ndays;     }
  unsigned duration()       const { return _duration;  }
  float    durationInDays() const { return _durationInDays; }
  float    fraction()       const { return _fraction;  }
  bool     springDST()      const { return _springDST; }
  bool     fallDST()        const { return _fallDST;   }



private:
  TDatime _t0;                   // Date at start of week, Sunday 00:00:00
  TDatime _tend;                 // Date at end of week, Saturday 23:59:59

  std::map<DataType,Data> _data; // Amount of data taken this week.

  unsigned _duration = 0;        // Duration of the week, in seconds ( DST Transistions are shorter or longer )
  float    _durationInDays = 0;  // _duration in units of floating point days.
  float    _fraction = 0;        // Fraction of the week within the plan; only different from 1 on first and last week.
  unsigned _ndays = 0;           // Number of days in the week; most weeks will be 7.  The first and last weeks may be truncated.
  bool     _springDST = false;   // This week contains a spring forward daylight savings transition
  bool     _fallDST   = false;   // This week contains a fall back daylight savings transition

  // Compute the date at the end of this week.
  TDatime endOfWeek_with_DST_adjustment( TDatime const& t0 );

};

std::ostream& operator<<(std::ostream& ost, const PlanWeek& pw );

#endif
