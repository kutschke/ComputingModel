#include "PlotMaker.hh"

#include "PlanInputs.hh"
#include "Plan.hh"


#include <iostream>
#include <stdexcept>

using std::cerr;
using std::cout;
using std::endl;

PlotMaker::PlotMaker ( PlanInputs const& inputs, Plan const& plan ):
  _inputs(inputs),
  _plan(plan){
  }

void PlotMaker::plotRawData (){
  cout << "PlotRawData ... " << _inputs.rootOutputFileName << endl;
}

