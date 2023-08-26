#ifndef RunPeriod_hh
#define RunPeriod_hh

//
// Information about one running period.
//
// Notes:
// 1) There are instancs of this class in both PlanInputs.hh and
//    Plan.hh.  The former holds only the information read from
//    the configuration file; the member datum _weeks is empty.
//    The latter has 2 phase construction - the core information
//    is copied from PlanInputs and the _weeks is filled in next.
//

#include "TDatime.h"
#include "Color.hh"
#include "RunType.hh"
#include "WeekIn.hh"

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
    fhicl::Atom<std::string> name    { Name{"name"},                     Comment{"A name for this running period."}};
    fhicl::Atom<std::string> type    { Name{"type"},                     Comment{"A name from the enum in RunType.hh."} };
    fhicl::Atom<std::string> start   { Name{"start"},                    Comment{"Starting date in format yyyy-mm-dd"}};
    fhicl::Atom<std::string> end     { Name{"end"},                      Comment{"Ending date in format yyyy-mm-dd"}};
    fhicl::Atom<std::string> color   { Name{"color"},                    Comment{"Name of a color for plotting the timeline of run periods. See Color.hh."}};
    fhicl::Atom<std::string> comment { Name{"comment"},                  Comment{"A human meaningfull description of this run period."}};
    fhicl::Atom<double>      liveFraction{ Name{"liveFraction"},         Comment{"Fraction of time that is live."}};
    fhicl::Atom<double>      triggerRejection{ Name{"triggerRejection"}, Comment{"Rejection factor for the trigger; typically 200 or 400."}};
  };

  RunPeriod( Config const& conf );

  RunType             type()              const { return _type;              }
  TDatime const&      startDate()         const { return _startDate;         }
  TDatime const&      endDate()           const { return _endDate;           }
  double              liveFraction()      const { return _liveFraction;      }
  double              triggerRejection()  const { return _triggerRejection;  }
  Color               color()             const { return _color;             }
  int                 nDays()             const { return _nDays;             }
  std::string const&  comment()           const { return _comment;           }

  // Alert: this is sometimes empty;  see note 1.
  std::vector<WeekIn> const & weeks() const { return _weeks; }

  // Add the week information.
  void addWeeks( std::vector<WeekIn> const& w);

  void printWeeks ( std::ostream& os, std::string const& prefix ) const;

private:
  TDatime     _startDate; // Whole day; no support for fractional days
  TDatime     _endDate;   // Whole day; no support for fractional days
  std::string _comment;   // Descriptive only

  // Alert.  Two phase construction. See note 1.
  // Weeks fully or partly within this run period.
  std::vector<WeekIn> _weeks;

  double      _liveFraction;      // Fraction of time spent running.
  double      _triggerRejection;  // The rejection factor of the trigger, 1:N, where N is typically 200 or 400.
  RunType     _type;              // From the enum.
  Color       _color;             // Used to plot the timeline of run periods.
  int         _nDays;             // Duration, in days.

};

std::ostream& operator<<(std::ostream& os, const RunPeriod& pw );

#endif
