#include "Plan.hh"

#include "constants.hh"
#include "dateHelpers.hh"

#include <cmath>
#include <iostream>
#include <stdexcept>

using std::cerr;
using std::cout;
using std::endl;

Plan::Plan( PlanInputs const& inp):_inp(inp){

  buildWeeks();
  buildMonths();

  if ( _inp.verbosity.buildPlan == 0 ){
    cout << "Number of weeks:  " << _weeks.size()  << endl;
    cout << "Number of months: " << _months.size() << endl;

  } else if ( _inp.verbosity.buildPlan > 0 && _inp.verbosity.buildPlan < 2 ){
    printWeeksSummary();
    printMonthsSummary( true );

  } else if ( _inp.verbosity.buildPlan >= 2 ){
    printAllWeeks();

    printAllMonths( true );
  }

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
  cout << "First week:       " << _months.front() << endl;
  if ( printWeeks ){
    _months.front().printWeeks( cout, "     " );
  }
  cout << "Last  week:       " << _months.back()  << endl;
  if ( printWeeks ){
    _months.back().printWeeks( cout, "     " );
  }
}
