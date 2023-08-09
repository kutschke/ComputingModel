#ifndef Run_hh
#define Run_hh

#include "TDatime.h"
#include "RunType.hh"

#include <iosfwd>

class Run{

public:

  // Needed for std::vector
  Run();

  RunType        type() const      { return _type;      }
  TDatime const& startDate() const { return _startDate; }
  TDatime const& endDate() const   { return _endDate;   }
  float          fraction() const  { return _fraction;  }

private:
  RunType _type;
  TDatime _startDate; // Whole day; no support for fractional days
  TDatime _endDate;   // Whole day; no support for fractional days
  float   _fraction;  // Fraction of nominal running time.

};

std::ostream& operator<<(std::ostream& os, const Run& pw );

#endif
