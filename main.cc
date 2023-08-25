#include "BB1.hh"
#include "BB2.hh"
#include "PlanInputs.hh"
#include "Plan.hh"
#include "PlotMaker.hh"

#include "sumYear.hh"

#include <iostream>

int main( int nargs, char** argc) {

  // Required argument is the name of the input file.
  if ( nargs != 2 ){
    std::cerr << "Must supply the name of a configuration file as an argument." << std::endl;
    return 1;
  }
  std::string configFile(argc[1]);

  // Read the input file.
  PlanInputs inp(configFile);
  inp.print();

  // Build the model.
  Plan plan(inp);

  // Make the plots etc
  PlotMaker pm( inp, plan);
  pm.plotRawData();

  // Under development.
  BB2 bb2;
  std::cout << "BB2 status: " << bb2.status() << std::endl;

  // Cross-check that sums over a typical year make sense
  sumYear( inp, plan, 2026, DataType::bb2OnSpill);
  sumYear( inp, plan, 2027, DataType::bb2OnSpill);
  sumYear( inp, plan, 2029, DataType::bb2OnSpill);
  sumYear( inp, plan, 2030, DataType::bb2OnSpill);
  sumYear( inp, plan, 2031, DataType::bb2OnSpill);
  sumYear( inp, plan, 2032, DataType::bb2OnSpill);
  sumYear( inp, plan, 2033, DataType::bb2OnSpill);

  inp.dumpRunPeriods ( "runPeriods.txt" );

  return 0;
}
