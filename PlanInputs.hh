#ifndef PlanInputs_hh
#define PlanInputs_hh

#include "DurationCalculator.hh"
#include "RunParameters.hh"
#include "RunPeriod.hh"

#include "TDatime.h"

struct PlanInputs{

public:

  struct Verbosity{
    unsigned inputs    = 0;
    unsigned buildPlan = 0;
  };

  PlanInputs( std::string const& filename );

  Verbosity verbosity;
  TDatime   startDate;
  TDatime   endDate;

  DurationCalculator duration;

  std::vector<RunPeriod> const& runs() const { return _runs; }

  float planDurationInDays() const;
  float planDurationInWeeks() const;
  float planDurationInMonths() const;
  float planDurationInQuarters() const;

  void print() const;

private:

  std::vector<RunPeriod>     _runs;
  std::vector<RunParameters> _runParameters;

  void goodInputsOrThrow();

};

#endif
