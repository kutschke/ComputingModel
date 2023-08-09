#ifndef Run_hh
#define Run_hh

#include "TDatime.h"
#include "RunType.hh"

#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/types/Atom.h"

#include <iosfwd>
#include <string>

class Run{

public:

  // Runtime configuration
  struct Config {
    using Name = fhicl::Name;
    using Comment = fhicl::Comment;
    fhicl::Atom<std::string> name    { Name{"name"}};
    fhicl::Atom<std::string> type    { Name{"type"}};
    fhicl::Atom<std::string> start   { Name{"start"}};
    fhicl::Atom<std::string> end     { Name{"end"}};
    fhicl::Atom<double>      fraction{ Name{"fraction"}};
  };

  Run(); // Needed to default construct an  std::vector<Run>?


  Run( Config const& conf );

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
