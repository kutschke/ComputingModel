//
// Display histograms of the computing model.
//
{

  // With this you can reinvoke the script without exiting root.
  gROOT->Reset();

  // Get rid of grey background (ugly for print out).
  gROOT->SetStyle("Plain");

  // No stats box
  gStyle->SetOptStat("");

  // Tell the axis system that our x axis is dates relative to the unix epoch,
  // not relative to the TDatime internal epoch of Jan 1 1995, 00:00:00 .
  gStyle->SetTimeOffset(0);

  TFile* file = new TFile( "draft0.root");

  TH1D* hraw;     file->GetObject("raw", hraw);
  TH1D* hrawInt;  file->GetObject("rawInt", hrawInt);

  TCanvas* c = new TCanvas("c", "Plots from draft0.root", 900, 900 );

  c->Divide(1,2);
  c->cd(1);    hraw->Draw("HIST");  hraw->GetXaxis()->SetTimeDisplay(1);    hraw->GetXaxis()->SetTimeFormat("%m/%d/%y");
  c->cd(2); hrawInt->Draw("HIST"); hrawInt->GetXaxis()->SetTimeDisplay(1); hrawInt->GetXaxis()->SetTimeFormat("%m/%d/%y");

}
