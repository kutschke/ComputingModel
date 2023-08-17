#ifndef PlotMaker_hh
#define PlotMaker_hh

class PlanInputs;
class Plan;

class PlotMaker{
public:
  PlotMaker ( PlanInputs const& inputs, Plan const& plan );

  void plotRawData ();

private:
  PlanInputs const& _inputs;
  Plan       const& _plan;

};

#endif
