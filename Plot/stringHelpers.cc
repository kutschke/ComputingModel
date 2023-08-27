#include "stringHelpers.hh"
#include <sstream>
#include <string>


std::string dateToString ( TDatime const& date ){
  ostringstream os;
  os << date.GetMonth() <<  "/" << date.GetDay() << "/" << date.GetYear();
  return os.str();
}
/*
std::string phaseToString ( Phase const& phase ){
  std::string s = phase.name + " (";
  s += dateToString(phase.start);
  s += ") - (";
  s += dateToString(phase.end);
  s += ")";
  return s;
}
*/
