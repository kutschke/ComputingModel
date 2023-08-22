#ifndef RunParameters_hh
#define RunParameters_hh

#include "constants.hh"
#include "RunType.hh"

#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/types/Atom.h"

#include <iosfwd>
#include <string>

class RunParameters{

public:

  // Configuration information for a Run Parameters object.
  struct Config {
    using Name = fhicl::Name;
    using Comment = fhicl::Comment;
    fhicl::Atom<std::string> type             { Name{"type"},             Comment{"A name from the enum in RunType.hh."} };
    fhicl::Atom<double>      eventSize        { Name{"eventSize"},        Comment{"Size of 1 event in kB"} };
    fhicl::Atom<double>      eventsPerDay     { Name{"eventsPerDay"},     Comment{"Number of events per day (untriggered) at 100% duty factor"} };
    fhicl::Atom<std::string> comment          { Name{"comment"},          Comment{"A human meaningfull description of this type of run."}};
  };

  RunParameters(){}

  RunParameters( Config const& conf );

  RunType     type()             const { return _type;             }
  double      eventSize()        const { return _eventSize;        } // TB
  double      eventsPerDay()     const { return _eventsPerDay;     }
  std::string comment()          const { return _comment;          }

  double   bytesPerDay()   const { return _eventSize*_eventsPerDay; } // TB
  double   eventsPerWeek() const { return _eventsPerDay*constants::daysPerWeek*liveFraction(); }
  double   bytesPerWeek()  const { return bytesPerDay()*constants::daysPerWeek*liveFraction(); }   // TB

  // Once shift per week of study time and/or maintenance.
  double liveFraction() const { return 20./21.; }

private:
  double      _eventSize;         // in TB
  double      _eventsPerDay;      // in TB
  std::string _comment;
  RunType     _type;              // From the enum.

};

std::ostream& operator<<(std::ostream& os, const RunParameters& pw );

#endif
