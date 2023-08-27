#ifndef Phase_hh
#define Phase_hh

#include "TDatime.h"
#include "Rtypes.h"
#include "TColor.h"

#include <iosfwd>
#include <string>

struct Phase{
  Phase();
  Phase( std::string const& name, TDatime const& start, TDatime const& end, EColor color = kBlack);
  Phase( std::string const& name, TDatime const& start, TDatime const& end, EColorPalette colorp);

  std::string name;
  TDatime start;
  TDatime end;
  EColor  color;

};

std::ostream& operator<<(std::ostream& os, const Phase& p );

#endif
