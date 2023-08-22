#include "BB2.hh"

#include "constants.hh"

#include <cmath>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

BB2::BB2(){

  /*
  constexpr double t_spill           = 0.0431; // Duration of one slow spill (s)
  constexpr double nSpillsPerMICycle = 8;      // Number of spills in one MI cycle
  */

  int nPulsesPerSpill = std::round(t_spill/constants::t_DR);

  int nPulsesPerMICycle = nPulsesPerSpill * nSpillsPerMICycle;
  double nPulsesPerDay = nPulsesPerMICycle * constants::nMICyclesPerDay;

  double nTriggeredEventsPerDay = nPulsesPerDay/400.;
  double eventSize = 400.*constants::kBToTB;
  double dataSizePerDay = nTriggeredEventsPerDay * eventSize;
  double dataSizePerYear = dataSizePerDay*365.25*0.67;

  double nTriggeredEventsPerYear = nTriggeredEventsPerDay*365.25*0.67;

  cout << "Pulses per spill :       " << nPulsesPerSpill   << endl;
  cout << "Pulses per MI Cycle :    " << nPulsesPerMICycle << endl;
  cout << "Pulses per Day:          " << nPulsesPerDay     << endl;
  cout << "nTriggeredEventsPerDay:  " << nTriggeredEventsPerDay  << endl;
  cout << "nTriggeredEventsPerYear: " << nTriggeredEventsPerYear << endl;
  cout << "eventSizePerDay: (TB)    " << dataSizePerDay          << endl;
  cout << "eventSizePerYear: (TB)   " << dataSizePerYear         << endl;

  /*
    constexpr int nBoosterCyclesPerMICycle = 21;
    constexpr double t_DR                  = 1.694E-6;                          // Period of Delivery Ring
    constexpr double t_booster             = 1./15.;                            // Period of booster
    constexpr double t_MI                  = t_booster*boosterCyclesPerMICycle; // Duration of one MI cycle
    constexpr double nMICyclesPerDay       = double(secondsPerDay)/t_MI;        // Number of MI cycles in one day
  */

}
