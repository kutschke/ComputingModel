#ifndef PlanInputs_hh
#define PlanInputs_hh

#include "DurationCalculator.hh"
#include "Run.hh"

#include "TDatime.h"

struct PlanInputs{

public:
  PlanInputs( std::string const& filename );

  TDatime startDate;
  TDatime endDate;

  DurationCalculator duration;

  std::vector<Run> const& runs() const { return _runs; }

  float planDurationInDays() const;
  float planDurationInWeeks() const;
  float planDurationInMonths() const;
  float planDurationInQuarters() const;

  void print() const;

private:

  std::vector<Run> _runs;

  void goodInputsOrThrow();

};

#endif
