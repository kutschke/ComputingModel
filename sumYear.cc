#include "sumYear.hh"

#include "PlanInputs.hh"
#include "Plan.hh"

#include <iomanip>
#include <iostream>
#include <stdexcept>
using std::cerr;
using std::cout;
using std::endl;

void sumYear( PlanInputs const& inputs, Plan const& plan, int year, DataType::enum_type dtype){
  double sumData(0.);
  double sumEvents(0.);
  double sumFraction(0.);
  int sumDays(0);
  for ( auto const& m : plan.months() ){
    if ( m.t0().GetYear() == year ) {
      for ( auto const& wi : m.weeksInMonth() ){
        auto idx = &wi.week()-plan.weeks().data();
        auto res = plan.resourcesPerWeek().at(idx);
        auto i = res.rawData.find( DataType(dtype) );
        if ( i != res.rawData.end() ){
          Data const& data = i->second;
          /*
          cout << "2030 Week:  "
             << wi.nDays() << " "
             << std::setw(10) <<  wi.fractionOfWeek() << " "
             << res.rawData.size() <<  " "
             << wi.week().t0().AsString() << " "
             << std::setw(7) << sumDays << " "
             << std::setw(10) << sumFraction
             << endl;
          */
          double f = 1.;
          //cout << "       sdata:  " << i->first << "  " << data << "   |  " << wi.nDays() << endl;
          if ( wi.nDays() !=7 && data.nDays() != 7 ){
            cerr << "Weird: both data and week are fractional.  Might be Ok but need to check. "
                 << "\nNumber of days in week: " << wi.nDays() << "  Number of days in data: " << data.nDays() << endl;
            throw std::logic_error("A case that I did not think could happen.");
          }
          f = wi.fractionOfWeek();
          double events = data.events();
          double size   = data.size();
          int    nDays  = data.nDays();
          if ( wi.nDays() != 7 && data.nDays() == 7){
            events *= f;
            size   *= f;
            nDays   = std::round( double(nDays)*f);
          } else if ( wi.nDays() ==7 && data.nDays() !=7 ){
            cout  << "Mark short week: " << endl;
            f = double(nDays)/7.;
          }
          sumData      += size;
          sumEvents    += events;
          sumFraction  += f;
          sumDays      += nDays;

        }
        /*
        cout << "        Sums:  "
             << std::setw(7) << sumDays << " "
             << std::setw(10) << sumFraction
             << endl;
        */

      }
    }
  }
  cout << "For year: " << year << endl;
  cout << "   Sum events:   " << sumEvents   << endl;
  cout << "   Sum data:     " << sumData     << endl;
  cout << "   Sum days:     " << sumDays     <<  " "  << double(sumDays)/7. << endl;
  cout << "   Sum fraction: " << sumFraction << endl;
}
