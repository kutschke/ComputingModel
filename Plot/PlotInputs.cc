#include "PlotInputs.hh"

#include "TColor.h"

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

PlotInputs::PlotInputs( std::string const& fileName ){
  ifstream in(fileName.c_str());
  while (in){
    std::string startTime, endTime, comment;
    int color;
    in >> std::quoted(startTime) >> std::quoted(endTime) >> color >>std::quoted(comment);
    if ( !in ){
      break;
    }
    TDatime start(startTime.c_str());
    TDatime end(endTime.c_str());
    //cout << "Period: " << start.AsString() << " " << end.AsString() << "  " << comment << endl;

    _phases.emplace_back( comment, start, end, static_cast<EColor>(color) );

  }
}

void PlotInputs::printPhases ( std::ostream& os ){
  for ( auto const& p : _phases ){
    os << p << endl;
  }
}
