#include "PlanInputs.hh"
#include "DurationCalculator.hh"

#include <array>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

PlanInputs::PlanInputs(){
  startDate.Set("2024-01-01 00:00:00");
  endDate.Set  ("2037-12-31 23:59:59");

  goodInputsOrThrow();

}

void PlanInputs::print() const{
  cout << "Plan start date:      " << startDate.AsString()     << endl;
  cout << "Plan end date:        " <<   endDate.AsString()     << endl;
  cout << "Duration in days:     " << planDurationInDays()     << endl;
  cout << "Duration in weeks:    " << planDurationInWeeks()    << endl;
  cout << "Duration in months:   " << planDurationInMonths()   << endl;
  cout << "Duration in quarters: " << planDurationInQuarters() << endl;

}

float PlanInputs::planDurationInDays( ) const {
  float d = duration.inDays( startDate, endDate);
  return d;
}

float PlanInputs::planDurationInWeeks( ) const {
  float d = duration.inWeeks( startDate, endDate);
  return d;
}

float PlanInputs::planDurationInMonths( ) const {
  float d = duration.inMonths( startDate, endDate);
  return d;
}

float PlanInputs::planDurationInQuarters() const{
  float d = duration.inQuarters( startDate, endDate);
  return d;
}

// Helper struct
struct MonthDay{
  MonthDay ( unsigned am, unsigned ad): m(am), d(ad){}
  //MonthDay ( int am, int ad): m(am), d(ad){}
  MonthDay ( TDatime const& dt ):m(dt.GetMonth()), d(dt.GetDay()){}

  unsigned m;
  unsigned d;
  bool operator==( const MonthDay& rhs) const{
    return (m == rhs.m && d == rhs.d);
  }

};

std::ostream& operator<<(std::ostream& os, const MonthDay& md ){
  os << "(" << md.m << "," << md.d << ")";
  return os;
}

void PlanInputs::goodInputsOrThrow(){

  if ( planDurationInWeeks() < 2. ){
    cerr << "Plan duration is less than 2 weeks.  No Supported" << endl;
    cerr << "Start date: " << startDate.AsString() << endl;
    cerr << "End date: "   << endDate.AsString() << endl;
    throw std::domain_error("Exit.  Invalid configuration.");
  }

  // Check that end date is after the start date.
  if ( planDurationInDays() <= 0. ){
    cerr << "Plan end data is before the start date." << endl;
    cerr << "Start date: " << startDate.AsString() << endl;
    cerr << "End date: "   << endDate.AsString() << endl;
    throw std::domain_error("Exit.  Inlegal end date.");
  }

  // Check that start date is on the first day of a quarter;
  MonthDay start(startDate);
  bool startOK = false;
  std::array<MonthDay,4> quarterStartDate{ MonthDay{1,1}, MonthDay{4,1}, MonthDay{7,1}, MonthDay{10,1}};
  for ( auto const& d : quarterStartDate){
    if ( start == d){
      startOK = true;
      break;
    }
  }
  if ( ! startOK ){
    cerr << "Plan start date must be the first day of a quarter but is not: "
         << startDate.AsString()
         << endl;
    throw std::domain_error("Exit.  Illegal start date.");
  }

  // Check that end date is on the last day of a quarter;
  std::array<MonthDay,4> quarterEndDate{ MonthDay{3,31}, MonthDay{6,30}, MonthDay{9,30}, MonthDay{12,31}};
  MonthDay end(endDate);
  bool endOK = false;
  for ( auto const& d : quarterEndDate){
    if ( end == d){
      endOK = true;
      break;
    }
  }
  if ( ! endOK ){
    cerr << "Plan end date must be the last day of a quarter but is not: "
         << endDate.AsString()
         << endl;
    throw std::domain_error("Exit.  Illegal end date.");
  }

}
