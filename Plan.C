//
// Run the Mu2e Computing Model and make plots
//
{
  gROOT->Reset();

  // Get rid of grey background (ugly for print out).
  gROOT->SetStyle("Plain");

  // Statistics box for histograms should include all of:
  // number of Entries, Mean, Rms, Underflows, Overflows
  gStyle->SetOptStat("");

#include "TDatime.h"
#include "RunType.cc+"
#include "Run.cc+"
#include "dateHelpers.cc+"
#include "PlanInputs.cc+"
#include "PlanMonth.cc+"
#include "PlanWeek.cc+"
#include "Plan.cc+"

  // Set inputs
  PlanInputs inp("draft0.fcl");
  inp.print();

  // Build the model.
  Plan plan(inp);


}
