#include "PlanInputs.hh"
#include "DurationCalculator.hh"
#include "RunParameters.hh"
#include "RunPeriod.hh"
#include "dateHelpers.hh"

#include "cetlib/filepath_maker.h"

#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Sequence.h"
#include "fhiclcpp/types/Table.h"

#include <array>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

namespace {
  using Name = fhicl::Name;
  using Comment = fhicl::Comment;

  struct VerbosityConfig{
    fhicl::Atom<unsigned> inputs{           Name{"inputs"},           Comment{"Control verboisty of printout when reading the input file."}};
    fhicl::Atom<unsigned> buildPlan{        Name{"buildPlan"},        Comment{"Control verboisty of printout when constructing the plan."}};
    fhicl::Atom<bool>     weeksInMonth{     Name{"weeksInMonth"},     Comment{"For each month, include the printout of the weeks in the month."}};
    fhicl::Atom<bool>     weeksInRunPeriod{ Name{"weeksInRunPeriod"}, Comment{"For each RunPeriod, include the printout of the weeks in the month."}};
  };

  struct PlanDuration {
    fhicl::Atom<std::string> start{ Name{"start"}, Comment{"Start date of the plan in format YYYY-MM-DD."}};
    fhicl::Atom<std::string> end{ Name{"end"},     Comment{"End date of the plan in format YYYY-MM-DD."}};
  };

  struct Config{
    fhicl::Table<VerbosityConfig>   verbosityConfig{Name("verbosity"), Comment{"Verbosity levels for different parts of the code."}};
    fhicl::Table<PlanDuration>      planDuration {Name("PlanDuration"), Comment{"Duration of the plan."}};
    fhicl::Atom<std::string>        rootOutputFileName { Name{"rootOutputFileName"}, Comment{"Name of the root output file that has histograms of resource use."}};
    fhicl::Sequence<fhicl::Table<RunPeriod::Config>> runs {Name("RunPeriods"),Comment{"A list of all of the run periods in the model."}};
    fhicl::Sequence<fhicl::Table<RunParameters::Config>> runParameters {Name("RunParameters"),Comment{"Parameters for each type of run: 1BB, 2BB, Cosmic."}};
  };

}

namespace {

  // Helper function to create a fcl table given a filename.
  fhicl::Table<Config> tableFromFile( std::string fileName ){
    cet::filepath_lookup policy("FHICL_FILE_PATH");
    fhicl::ParameterSet pSet{fhicl::ParameterSet::make(fileName, policy)};
    fhicl::Table<Config> config{pSet};
    return config;
  }

}

PlanInputs::PlanInputs( std::string const& fileName ){

  // Online help information.
  if ( fileName == "-?" || fileName == "--help" || fileName == "-h" ){

    // There is no default constructor for fhicl::Table<Config> and this is
    // a good enough way to implement it.
    auto config = tableFromFile( "help.fcl");
    config.print_allowed_configuration(std::cout);
    cout << "Exiting main program." << endl;
    exit(0);
  }

  // Create the configuration object from the input configuation file.
  cout << "PlanInputs filename: " << fileName << endl;
  auto config(tableFromFile(fileName));

  std::string start = config().planDuration().start();
  std::string end   = config().planDuration().end();

  startDate.Set( dayStart(start).c_str());
  endDate.Set  ( dayEnd(end).c_str());

  verbosity.inputs           = config().verbosityConfig().inputs();
  verbosity.buildPlan        = config().verbosityConfig().buildPlan();
  verbosity.weeksInMonth     = config().verbosityConfig().weeksInMonth();
  verbosity.weeksInRunPeriod = config().verbosityConfig().weeksInRunPeriod();

  rootOutputFileName = config().rootOutputFileName();

  std::vector<RunPeriod::Config> runs = config().runs();
  for ( RunPeriod::Config const& c : runs ){
    _runPeriods.emplace_back(c);
  }

  std::vector<RunParameters::Config> runParameters = config().runParameters();
  for ( RunParameters::Config const& c : runParameters ){
    RunType t = RunType(c.type());
    if ( t == RunType::unknown ){
      cerr << "Unsupported RunType: " << t << endl;
      throw std::domain_error("Exit.  Invalid configuration.");
    }
    auto i = _runParameters.emplace(std::make_pair(t,c));
    if ( !i.second ){
      cerr << "Attempt to add a duplicate RunParameters object.  Type: " << t << endl;
      throw std::domain_error("Exit.  Invalid configuration.");
    }
  }

  goodInputsOrThrow();

}

RunParameters const& PlanInputs::runParameters( RunType rt ) const{
  auto i = _runParameters.find(rt);
  if ( i == _runParameters.end() ){
    cerr << __func__  <<  "   RunParameters not found for this RunType: " << rt << endl;
    throw std::domain_error("RunParameters not found");
  }
  return i->second;
}

void PlanInputs::print() const{
  cout << "Plan start date:      " << startDate.AsString()       << endl;
  cout << "Plan end date:        " <<   endDate.AsString()       << endl;
  cout << "Duration in days:     " << planDurationInDays()       << endl;
  cout << "Duration in weeks:    " << planDurationInWeeks()      << endl;
  cout << "Duration in months:   " << planDurationInMonths()     << endl;
  cout << "Duration in quarters: " << planDurationInQuarters()   << endl;
  cout << "Root output filename: " << rootOutputFileName         << endl;
  cout << "Verbosity levels:"      << endl;
  cout << "   inputs:            " << verbosity.inputs           << endl;
  cout << "   buildPlan:         " << verbosity.buildPlan        << endl;
  cout << "   weeksInMonth:      " << verbosity.weeksInMonth     << endl;
  cout << "   weeksInRunPeriod:  " << verbosity.weeksInRunPeriod << endl;

  if ( verbosity.inputs <= 3 ){
    cout << "Number of run periods: " << _runPeriods.size() << endl;
  } else if ( verbosity.inputs >  3 ) {
    cout << "\nNumber of run periods: " << _runPeriods.size() << endl;
    for ( auto const& r : _runPeriods ){
      cout << " " << r << "\n" << endl;
    }
  }

  if ( verbosity.inputs <= 2 ){
    cout << "Number of sets of run parameters: " << _runParameters.size() << endl;
  } else if ( verbosity.inputs > 2 ) {
    cout << "\nNumber of sets of run parameters: " << _runParameters.size() << endl;
    for ( auto const& i : _runParameters ){
      cout << " " << i.second << "\n" << endl;
    }
  }

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

  if ( _runPeriods.empty() ){
    throw std::domain_error("No running periods specfiied.");
  }

  // Run periods must be complete and contiguous.
  if ( _runPeriods.front().startDate().Convert() != startDate.Convert() ){
    cerr << "First run period does not start at start date of the plan."
         << "\n  Start of first run period: " << _runPeriods.front().startDate().AsString()
         << "\n  Start of the plan:         " << startDate.AsString()
         << endl;
    throw std::domain_error("First run period has improper start date.");
  }

  if ( _runPeriods.back().endDate().Convert() != endDate.Convert() ){
    cerr << "Last run period does not end at the end date of the plan."
         << "\n  End of last run period: " << _runPeriods.back().endDate().AsString()
         << "\n  End of the plan:        " << endDate.AsString()
         << endl;
    throw std::domain_error("Last run period has improper end date.");
  }

  unsigned nBad{0};
  for ( size_t i=1; i<_runPeriods.size(); ++i ){
    auto delta = _runPeriods.at(i).startDate().Convert() - _runPeriods.at(i-1).endDate().Convert();
    if ( delta != 1 ){
      ++nBad;
      cerr << "Running period " << i << " is not contiguous with it's predecessor."
           << "\nRun period: " << i-1 << "\n" <<  _runPeriods.at(i-1)
           << "\nRun period: " << i   << "\n" <<  _runPeriods.at(i)
           << endl;
    }
  }
  if ( nBad != 0 ){
    throw std::domain_error("Non-contiguous running periods.");
  }

  // Except for frst and last, run periods must start on Monday and end on Saturday.
  int nBad2{0};
  size_t last = _runPeriods.size()-1;
  for ( size_t i = 0; i< _runPeriods.size(); ++i ) {
    auto const& rp = _runPeriods.at(i);
    auto d0 = dayOfWeek ( rp.startDate() );
    if ( i != 0 &&  d0 != 0 ){
      cerr << "Start date of a RunPeriod is not a Sunday."
           << "\n   RunPeriod: " << rp << endl;
      ++nBad2;
    }
    auto d1 = dayOfWeek( rp.endDate() );
    if ( i != last && d1 != 6 ){
      cerr << "End date of a RunPeriod is not a Saturday."
           << "\n   RunPeriod: " << rp << endl;
      ++nBad2;
    }
  }
  if ( nBad2 != 0 ){
    throw std::domain_error("Some RunPeriods have invalid start or end dates.");
  }


  // Warnings if the summer shutdowns are not 12 weeks.
  for ( auto const& rp : _runPeriods ){
    auto i = rp.comment().find("Summer");
    if ( i != std::string::npos ){
      DurationCalculator dc;
      auto w = dc.inWeeks( rp.startDate(), rp.endDate() );
      int iw = std::round(w);
      if ( iw != 12 ){
        cerr << "\nWarning: summer shutdown is not 12 weeks long.  Hope that's OK."
             << "\n" << rp << endl;
      }
    }
  }

  // Require RunParameters to be complete (excluding RunType::unknown).
  if (  _runParameters.size() != RunType::size()-1 ){
    cerr << "Missing specification of RunParameters "
         << "\n Number of RunParameters in the input file:    " << _runParameters.size()
         << "\n Number of values in enum (excluding unknown): " << RunType::size()-1;
    throw std::domain_error("Missing values in the RunParameters stanza.");
  }


}
