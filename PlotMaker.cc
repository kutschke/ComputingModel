#include "PlotMaker.hh"

#include "constants.hh"
#include "PlanInputs.hh"
#include "Plan.hh"

#include "TFile.h"
#include "TH1D.h"

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

  TFile* file = new TFile( _inputs.rootOutputFileName.c_str(), "RECREATE"  );

  // Find the first day of the first week and the last day of the last week.
  int start{-1}, end{-1};
  for ( size_t i=0; i<_plan.resourcesPerWeek().size(); ++i ){
    auto const& r =  _plan.resourcesPerWeek().at(i);
    if ( !r.rawData.empty() ){
      //size_t s= r.rawData.size();
      //if ( s > 1 ){
      //  cout << "s>1  " << s << " " << _plan.weeks().at(i).t0().AsString() << endl;
      //}
      if ( start == -1 ){
        start = i;
      }
      end = i;
    }
  }
  PlanWeek const& w0 = _plan.weeks().at(start);
  PlanWeek const& w1 = _plan.weeks().at(end);

  // Number of weeks in the plan.  Rounding needed to deal with daylight savings time.
  double anWeeks = double(w1.tend().Convert() - w0.t0().Convert())/constants::secondsPerWeek;
  long   nWeeks  = lrint(anWeeks);

  // Offset to define bin center relative to bin lower edge
  double halfWeek = 0.5*double(constants::secondsPerWeek);

  TH1D* hraw    = new TH1D( "raw",    "On-spill Raw Data vs time;;(TB)",          nWeeks, w0.t0().Convert(), w1.tend().Convert() );
  TH1D* hrawInt = new TH1D( "rawInt", "On-spill Raw Data Integral vs time;;(TB)", nWeeks, w0.t0().Convert(), w1.tend().Convert() );

  std::vector<double> zero(nWeeks,0);

  double sum{0.};
  for ( size_t i=0; i<_plan.resourcesPerWeek().size(); ++i ){
    Resources const& r = _plan.resourcesPerWeek().at(i);
    PlanWeek  const& w = _plan.weeks().at(r.index);

    // Bin center for this week
    double t = w.t0().Convert() + halfWeek;

    for ( auto const& j : r.rawData ){
      double datasize = j.second.size();
      //cout << "   Data: " << i << " " << j.second << endl;
      hraw->Fill( t, datasize);
      sum+=datasize;
    }
    hrawInt->Fill(t, sum);

  } // end loop over resource weeks

  // Tell root that none of the bins have errors.
  hraw   ->SetError( zero.data() );
  hrawInt->SetError( zero.data() );

  cout << "Total data size(TB): " << sum << endl;

  file->Write();
  file->Close();

}

