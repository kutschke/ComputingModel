#include "Color.hh"

std::string const& ColorDetail::typeName() {
  static std::string type("Color");
  return type;
}

std::map<ColorDetail::enum_type,std::string> const& ColorDetail::names(){

  static std::map<enum_type,std::string> nam;

  if ( nam.empty() ){
    nam[unknown]          = "unknown";
    nam[white]            = "white";
    nam[black]            = "black";
    nam[gray]             = "gray";
    nam[red]              = "red";
    nam[blue]             = "blue";
    //nam[] = "";
  }

  return nam;
}
