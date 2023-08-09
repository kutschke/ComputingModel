#ifndef RunPeriod_hh
#define RunPeriod_hh

#include "TDatime.h"
#include "RunType.hh"

#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/types/Atom.h"

#include <iosfwd>
#include <string>

class RunPeriod{

public:

  // RunPeriodtime configuration
  struct Config {
    using Name = fhicl::Name;
    using Comment = fhicl::Comment;
    fhicl::Atom<std::string> name    { Name{"name"},     Comment{"A name for this running period."}};
    fhicl::Atom<std::string> type    { Name{"type"},     Comment{"A name from the enum in RunType.hh."} };
    fhicl::Atom<std::string> start   { Name{"start"},    Comment{"Starting date in format yyyy-mm-dd"}};
    fhicl::Atom<std::string> end     { Name{"end"},      Comment{"Ending date in format yyyy-mm-dd"}};
    fhicl::Atom<std::string> comment { Name{"comment"},  Comment{"A human meaningfull description of this run period."}};
    fhicl::Atom<double>      fraction{ Name{"fraction"}, Comment{"Fraction of time that is live."}};
  };

  RunPeriod(); // Needed to default construct an  std::vector<RunPeriod>?


  RunPeriod( Config const& conf );

  RunType            type()      const { return _type;      }
  TDatime const&     startDate() const { return _startDate; }
  TDatime const&     endDate()   const { return _endDate;   }
  float              fraction()  const { return _fraction;  }
  std::string const& comment()   const { return _comment;   }

private:
  TDatime     _startDate; // Whole day; no support for fractional days
  TDatime     _endDate;   // Whole day; no support for fractional days
  std::string _comment;   // Descriptive only
  float       _fraction;  // Fraction of time spent running.
  RunType     _type;      // From the enum.

};

std::ostream& operator<<(std::ostream& os, const RunPeriod& pw );

#endif
