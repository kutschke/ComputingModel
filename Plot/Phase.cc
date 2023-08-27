#include "Phase.hh"

#include <iostream>

Phase::Phase(){}
Phase::Phase( std::string const& name, TDatime const& start, TDatime const& end, EColor color):
    name(name), start(start), end(end), color(color){}
Phase::Phase( std::string const& name, TDatime const& start, TDatime const& end, EColorPalette colorp):
    name(name), start(start), end(end), color(static_cast<EColor>(colorp)){}


std::ostream& operator<<(std::ostream& os, const Phase& p ){
  os << "Start: "   << p.start.AsString()
     << "  End: "   << p.end.AsString()
     << "  Color: " << p.color
     << "   "       << p.name;
  return os;
}
