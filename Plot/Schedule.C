//
// Display the run perids defined in the computing model.
//
{

  gROOT->Reset();

  // Get rid of grey background (ugly for print out).
  gROOT->SetStyle("Plain");

  // No stats box for histograms.
  gStyle->SetOptStat("");

  // On the x axis, t=0 is the unix epoch.
  gStyle->SetTimeOffset(0);

#include "TDatime.h"
#include "Phase.cc+"
#include "PlotInputs.cc+"

  PlotInputs inp("draft0_runPeriods.txt");
  std::vector<Phase> const& phases{inp.phases()};
  cout << "Number of phases: " << inp.phases().size() << endl;

  TDatime const& plotStart(inp.start());
  TDatime const& planEnd(inp.end());

#include "DurationCalculator.hh"
  DurationCalculator duration;

  int nQuarters =std::ceil(duration.inQuarters(plotStart, planEnd));
  double seconds  = duration.inSeconds(plotStart, planEnd);
  cout << "Plan duration: "
       << duration.inQuarters(plotStart, planEnd) << " quarters;"
       << duration.inYears(plotStart, planEnd) << " years;"
       << nQuarters << " quarters rounded up."
       << endl;


  // Define the minimum box size used for plotting.
  TDatime tmp1(2020, 1,1,0,0,0);
  TDatime tmp2(2020, 1,2,0,0,0);
  double day=tmp2.Convert()-tmp1.Convert();
  double minboxsize=14*day;

  TCanvas *canvas = new TCanvas("c","Data Processing Plan", 1600, 1600 );

  TH1F* frame = new TH1F( "frame", "Mu2e Computing Model Strawman Schedule", nQuarters, plotStart.Convert(), planEnd.Convert() );

  double hmax = phases.size()+1;

  frame->Draw();
  frame->SetMinimum(0.);
  frame->SetMaximum(hmax);
  frame->GetXaxis()->SetTimeDisplay(1);
  frame->GetXaxis()->SetLabelSize(0.02);
  frame->GetXaxis()->SetTimeFormat("%m/%d/%y");
  frame->GetYaxis()->SetLabelSize(0.02);


  // Duration of half of one quarter - used to space the phase labels
  auto halfQuarter = ( TDatime(2020,4,1,0,0,0).Convert() - TDatime(2020,1,1,0,0,0).Convert() )/2;

#include "stringHelpers.cc+"

  TBox* box = new TBox;

  TText* text = new TText;
  box->SetFillStyle(1001);
  text->SetTextAlign(11);
  text->SetTextSize(0.02);
  double phaseNameOffset = 0.2/8.*hmax;

  for ( size_t i=0; i<phases.size(); ++i ){
    auto const& phase = phases[i];
    int k=phases.size()-1-i;
    double high = k + 1 + 0.25;
    double low  = k + 1 - 0.25;
    double mid  = k+1;
    box->SetLineColor(phase.color);
    box->SetFillColor(phase.color);
    double dt0 = phase.end.Convert() - phase.start.Convert();
    double dt = std::max( dt0, minboxsize);
    box->DrawBox( phase.start.Convert(), low, phase.start.Convert()+dt, high);

    text->SetTextColor( phase.color );

    TString name = TString(phase.name);
    if ( i < phases.size()/2+2){
      text->SetTextAlign(12);
      text->DrawText( phase.end.Convert()+halfQuarter, mid, name);
    } else{
      text->SetTextAlign(32);
      text->DrawText( phase.start.Convert()-halfQuarter*1.75, mid, name );
    }

  }

  canvas->Print("Schedule.pdf");

}
