#ifndef Plan_hh
#define Plan_hh


#include "DurationCalculator.hh"
#include "PlanInputs.hh"
#include "PlanWeek.hh"
#include "PlanMonth.hh"

#include <vector>

class Plan{

public:
  Plan( PlanInputs const& inp );

  void print() const;

  void printAllWeeks() const;
  void printWeeksSummary() const;

  void printAllMonths        ( bool printWeeks = false) const;
  void printMonthsSummary    ( bool printWeeks = false) const;
  void printRunPeriodsSummary( bool printWeeks = false) const;

private:
  DurationCalculator     _dCalc;
  PlanInputs const&      _inp;
  std::vector<PlanWeek>  _weeks;
  std::vector<PlanMonth> _months;
  std::vector<RunPeriod> _runPeriods;

  void buildWeeks();
  void buildMonths();
  void buildRunPeriods();

};

#endif
