#ifndef PlanInputs_hh
#define PlanInputs_hh

#include "DurationCalculator.hh"

#include "TDatime.h"

struct PlanInputs{

public:
  //PlanInputs();
  PlanInputs( std::string const& filename );

  TDatime startDate;
  TDatime endDate;

  DurationCalculator duration;

  float planDurationInDays() const;
  float planDurationInWeeks() const;
  float planDurationInMonths() const;
  float planDurationInQuarters() const;
  void print() const;

private:
  void goodInputsOrThrow();

};

#endif
