#ifndef PlanInputs_hh
#define PlanInputs_hh

#include "DurationCalculator.hh"
#include "RunPeriod.hh"

#include "TDatime.h"

struct PlanInputs{

public:
  PlanInputs( std::string const& filename );

  TDatime startDate;
  TDatime endDate;

  DurationCalculator duration;

  std::vector<RunPeriod> const& runs() const { return _runs; }

  float planDurationInDays() const;
  float planDurationInWeeks() const;
  float planDurationInMonths() const;
  float planDurationInQuarters() const;

  void print() const;

private:

  std::vector<RunPeriod> _runs;

  void goodInputsOrThrow();

};

#endif
