#include "PlanInputs.hh"
#include "Plan.hh"
#include "PlotMaker.hh"

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

  return 0;
}
