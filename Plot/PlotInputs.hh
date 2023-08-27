#ifndef PlotInputs_hh
#define PlotInputs_hh

//
// Read the inputs to make the plots
//

#include "Phase.hh"

#include <iosfwd>
#include <string>
#include <vector>

class PlotInputs{

public:
  PlotInputs( std::string const& fileName );

  std::vector<Phase> const& phases() const { return _phases; }

  void printPhases ( std::ostream& );

  TDatime const& start() const { return _phases.front().start; }
  TDatime const& end()   const { return _phases.back().end;    }

private:

  std::vector<Phase> _phases;

};

#endif
