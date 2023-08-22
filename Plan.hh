#ifndef Plan_hh
#define Plan_hh

#include "DurationCalculator.hh"
#include "PlanInputs.hh"
#include "PlanWeek.hh"
#include "PlanMonth.hh"
#include "Resources.hh"

#include <vector>

class Plan{

public:
  Plan( PlanInputs const& inp );

  std::vector<PlanWeek>  const& weeks()            const { return  _weeks;            }
  std::vector<PlanMonth> const& months()           const { return  _months;           }
  std::vector<Resources> const& resourcesPerWeek() const { return  _resourcesPerWeek; }

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

  // In lock step with PlanWeek.
  std::vector<Resources> _resourcesPerWeek;

  void buildWeeks();
  void buildMonths();
  void buildRunPeriods();

  void initializeResources();
  void addRawData();

};

#endif
