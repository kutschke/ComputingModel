#ifndef PlanInputs_hh
#define PlanInputs_hh

#include "DurationCalculator.hh"
#include "RunParameters.hh"
#include "RunPeriod.hh"

#include "TDatime.h"

#include <string>
#include <vector>
#include <map>

struct PlanInputs{

public:

  struct Verbosity{
    unsigned inputs           = 0;
    unsigned buildPlan        = 0;
    bool     weeksInMonth     = false;
    bool     weeksInRunPeriod = false;
  };

  PlanInputs( std::string const& filename );

  Verbosity verbosity;
  TDatime   startDate;
  TDatime   endDate;

  std::string rootOutputFileName;

  DurationCalculator duration;

  std::vector<RunPeriod> const& runPeriods() const { return _runPeriods; }

  RunParameters const& runParameters( RunType rt ) const;

  float planDurationInDays() const;
  float planDurationInWeeks() const;
  float planDurationInMonths() const;
  float planDurationInQuarters() const;

  void print() const;

  // Write run periods to a file for processing by a root Macro.
  void dumpRunPeriods( std::string const& baseFileName) const;

private:

  std::vector<RunPeriod>          _runPeriods;
  std::map<RunType,RunParameters> _runParameters;

  void goodInputsOrThrow();

};

#endif
