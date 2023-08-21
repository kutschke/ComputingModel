
#include "Plan.hh"
#include "LocateWeekRange.hh"
#include "constants.hh"
#include "dateHelpers.hh"

#include <cmath>
#include <iostream>
#include <stdexcept>

using std::cerr;
using std::cout;
using std::endl;

Plan::Plan( PlanInputs const& inp):
  _inp(inp),
  _runPeriods(inp.runPeriods()){

  // Initialize the data members _weeks, _months, _runPeriods
  buildWeeks();
  buildMonths();
  buildRunPeriods();

  initializeResources();

  // Add the raw data to the weeks.
  addRawData();

  print();

  /*
  // For debugging
  for ( auto const& res : _resourcesPerWeek ){
    if ( ! res.rawData.empty() ) {
      cout << res.index << " " << _weeks[res.index] << endl;
      for ( auto const& raw : res.rawData ){
        cout << "   " << raw.first << "  |  " << raw.second << endl;
      }
    }
  }
  */


}

void Plan::buildWeeks(){
  // The number of seconds since the epoch at the end of the plan.
  auto const planEndConvert = _inp.endDate.Convert();

  // Create week 0.
  _weeks.emplace_back(_inp.startDate, _inp.endDate);
  auto last = _weeks.back().tend().Convert();

  // Self consistency check.
  if ( last > planEndConvert ){
    cerr << "First week ends after the end of plan: " << endl;
    cerr << "   Start of first week: " << _weeks.back().t0().AsString() << endl;
    cerr << "   End of first week:   " << _weeks.back().tend().AsString() << endl;
    cerr << "   End of plan:         " << _inp.endDate.AsString() << endl;
    throw std::logic_error("First week ends after the end of the plan.");
  }

  // Create the remaining weeks
  int const nweeks = std::ceil(_dCalc.inWeeks( _inp.startDate, _inp.endDate));
  for ( int i=0; i<nweeks; ++i ){

    // Next week starts Sunday 00:00:00 following the last second of the previous week.
    TDatime t(last+1);
    _weeks.emplace_back(t, _inp.endDate);
    last = _weeks.back().tend().Convert();

    if ( last >= planEndConvert ){
      break;
    }

  }

  // Self-consistency check.
  if  ( _weeks.back().tend().Convert() != planEndConvert ){
    cerr << "End date of final week does not match the requested end date of the plan."  << endl;
    cerr << "End date of final week: " << _weeks.back().tend().AsString()                << endl;
    cerr << "End date of plan:       " << _inp.endDate.AsString()                        << endl;
    throw std::logic_error("Exit.  Month table was not built properly.");
  }
}

void Plan::buildMonths(){

  // The number of seconds since the epoch at the end of the plan.
  auto const planEndConvert = _inp.endDate.Convert();

  // This is a rough estimate and will usually be a little high.
  // I uses a constant 30 day month.
  int nMonths = std::ceil(_inp.planDurationInMonths());

  // Build the first month
  _months.emplace_back( _inp.startDate, planEndConvert, _weeks );
  auto last = _months.back().tend().Convert();

  // Build remaining months.
  for ( int i=0; i<nMonths; ++i ){
    TDatime monthStart(last+1);
    _months.emplace_back( monthStart, planEndConvert, _weeks );
    last = _months.back().tend().Convert();
    if ( last == planEndConvert ){
      break;
    }
    if ( last > planEndConvert ){
      cerr << "Month ends after the end of plan: " << endl;
      cerr << "   Start of the month:  " << _months.back().t0().AsString() << endl;
      cerr << "   End of the  month:   " << _months.back().tend().AsString() << endl;
      cerr << "   End of plan:         " << _inp.endDate.AsString() << endl;
      throw std::logic_error("Month ends after the end of the plan.");
    }
  }

}

// Loop over the run periods and add raw data to the weeks.
void Plan::buildRunPeriods(){

  for ( auto& r : _runPeriods ){

    // Temporary that will be copied into the RunPeriod.
    std::vector<WeekIn> weeksIn;

    // Loop over weeks in this run period.
    unsigned sumDays{0};
    auto t0   = r.startDate().Convert();
    auto tend = r.endDate().Convert();
    LocateWeekRange range( r.startDate(), r.endDate(), _weeks );

    // Alert: range is closed at both ends, not half-open.
    for ( size_t i = range.firstWeek(); i < range.lastWeek()+1; ++i ){
      PlanWeek& w = _weeks.at(i);
      unsigned nDays{0};
      auto wt0   = w.t0().Convert();
      auto wtend = w.tend().Convert();
      if ( wt0 >= t0 && wtend <= tend ){
        nDays = w.nDays();
      } else if ( wt0 >= t0 ){
        auto lastDay = dayOfWeek( r.endDate());
        auto firstDay = dayOfWeek( w.t0() );
        nDays = lastDay-firstDay+1;
      } else if ( wtend <= tend ){
        auto firstDay = dayOfWeek( r.startDate());
        auto lastDay  = dayOfWeek( w.tend() );
        nDays = lastDay-firstDay+1;
      } else{
        cerr << __func__ << "Failure of LocateWeekRange or its interpretation."
             << "\nRun Period: " << r
             << "\nWeek:       " << w
             << endl;
        throw std::logic_error("Failure of LocateWeekRange.");
      }
      sumDays += nDays;
      weeksIn.emplace_back( w, nDays);
    } // end loop over weeks

    r.addWeeks( weeksIn );

    auto duration = _dCalc.inDays( r.startDate(), r.endDate() );

    // Cross-check.  Note that duration is aware of daylight savings but sumDays is not.
    if ( std::abs( duration- double(sumDays)) > 0.1 ){
      cerr << "Error processing run periods:"
           << "\n" << r
           << "\n Sum of over weeks: " << sumDays << "   Duration (days): " << duration
           << endl;
      throw std::logic_error("Error processing run periods.");
    }

  } // end loop over runPeriods
} // end buildRunPeriods

void Plan::initializeResources(){
  _resourcesPerWeek.reserve(_weeks.size());
  for ( size_t i=0; i<_weeks.size(); ++i ){
    _resourcesPerWeek.emplace_back(i);
  }
}


void Plan::addRawData() {

  for ( auto& runPeriod : _runPeriods ){
    //cout << "Period: " << runPeriod << endl;
    if ( runPeriod.type() == RunType::bb1 || runPeriod.type() == RunType::bb2 ){
      RunParameters const& params= _inp.runParameters(runPeriod.type());
      //cout << "Run params: " << params << endl;
      double rpLiveFraction = runPeriod.fraction();
      for ( auto const& w : runPeriod.weeks() ){
        size_t iw = &w.week()-&_weeks.front();
        //cout << "       week: " << w << " " << iw << endl;
        // Fixme: need a more general solution for this
        auto dt = ( runPeriod.type() == RunType::bb1 ) ? DataType::bb1OnSpill : DataType::bb2OnSpill;
        double fractionOfWeek = w.fraction();     //  Fraction of the week that is in this running period.
        double f = rpLiveFraction*fractionOfWeek;
        Data tmp( DataType(dt), params.eventsPerWeek()*f, params.bytesPerWeek()*f );
        //cout <<  "          data: "  << tmp << endl;
        //cout <<  "          check: " << iw << "  " << _resourcesPerWeek[iw].index << endl;
        _resourcesPerWeek[iw].addRawData(tmp);

      }
    }
  } // end Loop over run periods.

} // end addRawData

void Plan::print() const {

  if ( _inp.verbosity.buildPlan == 0 ){
    cout << "Number of weeks:  " << _weeks.size()  << endl;
    cout << "Number of months: " << _months.size() << endl;

  } else if ( _inp.verbosity.buildPlan > 0 && _inp.verbosity.buildPlan < 2 ){
    printWeeksSummary();
    printMonthsSummary    ( _inp.verbosity.weeksInMonth     );
    printRunPeriodsSummary( _inp.verbosity.weeksInRunPeriod );

  } else if ( _inp.verbosity.buildPlan >= 2 ){
    printAllWeeks();
    printAllMonths( _inp.verbosity.weeksInMonth );
  }


} // end print

void Plan::printAllWeeks() const{
  cout << "\nNumber of weeks: " << _weeks.size()  << endl;
  for ( auto const& w : _weeks ){
    cout << w << endl;
  }
}

void Plan::printAllMonths( bool printWeeks) const{
  cout << "\nNumber of months: " << _months.size()  << endl;
  for ( auto const& m : _months ){
    cout << m << endl;
    if ( printWeeks ){
      m.printWeeks( cout, "    ");
    }
  }
}

void Plan::printWeeksSummary() const{
  cout << "\nNumber of weeks: " << _weeks.size()  << endl;
  cout << "First week:      " << _weeks.front() << endl;
  cout << "Last  week:      " << _weeks.back()  << endl;
}

void Plan::printMonthsSummary( bool printWeeks ) const{
  cout << "\nNumber of months: " << _months.size()  << endl;
  cout << "First Month:       " << _months.front() << endl;
  if ( printWeeks ){
    _months.front().printWeeks( cout, "     " );
  }
  cout << "Last  Month:       " << _months.back()  << endl;
  if ( printWeeks ){
    _months.back().printWeeks( cout, "     " );
  }
}

void Plan::printRunPeriodsSummary( bool printWeeks ) const{
  cout << "\nNumber of RunPeriods: " << _runPeriods.size()  << endl;
  cout << "     First RunPeriod:        " << _runPeriods.front() << endl;
  if ( printWeeks ){
    _runPeriods.front().printWeeks( cout, "         " );
  }
  cout << "     Last  RunPeriod:        " << _runPeriods.back()  << endl;
  if ( printWeeks ){
    _runPeriods.back().printWeeks( cout, "         " );
  }

}
