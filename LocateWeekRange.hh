#ifndef LocateWeekRange_hh
#define LocateWeekRange_hh

#include "PlanWeek.hh"

class LocateWeekRange {

public:

  LocateWeekRange ( TDatime const& t0, TDatime const& t1, std::vector<PlanWeek> const& weeks );

  size_t firstWeek() const { return _firstWeek; }
  size_t lastWeek() const { return _lastWeek; }

  size_t nWeeks() const;

private:

  static constexpr size_t unInitialized = 999999999999;

  size_t _firstWeek = unInitialized;
  size_t _lastWeek  = unInitialized;

};

#endif
