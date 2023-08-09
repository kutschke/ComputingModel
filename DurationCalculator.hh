#ifndef DurationCalculator_hh
#define DurationCalculator_hh

#include "TDatime.h"

class DurationCalculator{
public:
  DurationCalculator():
    _day(TDatime(2021,1,2,0,0,0).Convert()-TDatime(2021,1,1,0,0,0).Convert()),
    _daysPerWeek(7),
    _daysPerMonth(30),
    _daysPerYear(365){
  }

  float inSeconds( TDatime const& t0, TDatime const& t1) const{
    return (t1.Convert()-t0.Convert());
  }

  float inDays( TDatime const& t0, TDatime const& t1) const{
    return (float(t1.Convert()-t0.Convert()))/_day;
  }

  float inWeeks( TDatime const& t0, TDatime const& t1) const{
    return (float(t1.Convert()-t0.Convert()))/_day/_daysPerWeek;
  }

  // Always use a fixed length month.
  float inMonths( TDatime const& t0, TDatime const& t1) const{
    return (float(t1.Convert()-t0.Convert()))/_day/_daysPerMonth;
  }

  float inQuarters( TDatime const& t0, TDatime const& t1) const{
    return inYears(t0,t1)*4.;
  }

  float inYears( TDatime const& t0, TDatime const& t1) const{
    return (float(t1.Convert()-t0.Convert()))/_day/_daysPerYear;
  }

private:
  // Duration of 1 day in TDatime units (seconds)
  UInt_t _day;
  UInt_t _daysPerWeek;
  UInt_t _daysPerMonth;
  UInt_t _daysPerYear;
  //static constexpr UInt_t _daysPerWeek  =   7;
  //static constexpr UInt_t _daysPerMonth =  30;
  //static constexpr UInt_t _daysPerYear  = 365;
};

#endif
