#include "LocateWeekRange.hh"

#include <iostream>
using std::endl;
using std::cerr;
using std::cout;

LocateWeekRange::LocateWeekRange ( TDatime const& t0, TDatime const& t1, std::vector<PlanWeek> const& weeks ){

  size_t i{0};
  auto t0Convert = t0.Convert();
  auto t1Convert = t1.Convert();
  for ( ; i<weeks.size(); ++i ){
    PlanWeek const& w{weeks.at(i)};
    if ( t0Convert >= w.t0().Convert() && t0Convert <= w.tend().Convert() ){
      break;
    }
  }
  _firstWeek=i;

  size_t j{i};
  for ( ; j<weeks.size(); ++j ){
    PlanWeek const& w{weeks.at(j)};
    if ( t1Convert >= w.t0().Convert() && t1Convert <= w.tend().Convert() ){
      break;
    }
  }
  _lastWeek = j;

}

size_t LocateWeekRange::nWeeks() const{
  if ( _firstWeek == unInitialized || _lastWeek == unInitialized || _firstWeek > _lastWeek ){
    cerr << __func__ << "  First and last week do not make sense."
         << "\n  First Week: " << _firstWeek
         << "\n  Last Weeek: " << _lastWeek
         << endl;
    throw std::logic_error("Week range does not make sense.");
  }
  return _lastWeek-_firstWeek+1;
}
