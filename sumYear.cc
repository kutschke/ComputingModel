#include "sumYear.hh"

#include "PlanInputs.hh"
#include "Plan.hh"

#include <iostream>
using std::cout;
using std::endl;

void sumYear( PlanInputs const& inputs, Plan const& plan, int year){
  double sumData(0.);
  double sumEvents(0.);
  double sumFraction(0.);
  for ( auto const& m : plan.months() ){
    if ( m.t0().GetYear() == year ) {
      //cout << m.t0().AsString() << endl;
      for ( auto const& wi : m.weeksInMonth() ){
        auto idx = &wi.week()-plan.weeks().data();
        auto res = plan.resourcesPerWeek().at(idx);
        //cout << "      " << idx <<  "   " << res.index << "  |  " << wi << endl;
        for ( auto const& i : res.rawData ){
          //cout << "           " << i.first << "  " << i.second << endl;
          sumData +=  i.second.size();
          sumEvents += i.second.events();
        }
        if ( res.rawData.size() > 0 ) {
          sumFraction += wi.fraction();
        }
      }
    }
  }
  cout << "For year: " << year << endl;
  cout << "   Sum events:   " << sumEvents   << endl;
  cout << "   Sum data:     " << sumData     << endl;
  cout << "   Sum fraction: " << sumFraction << endl;
}
