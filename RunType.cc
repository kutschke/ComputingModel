//
// Enum-matched-to-String class for defining run types.
//

#include "RunType.hh"

std::string const& RunTypeDetail::typeName() {
  static std::string type("RunType");
  return type;
}

std::map<RunTypeDetail::enum_type,std::string> const& RunTypeDetail::names(){

  static std::map<enum_type,std::string> nam;

  if ( nam.empty() ){
    nam[unknown]          = "unknown";
    nam[noData]           = "noData";
    nam[cosmicCalOnly]    = "cosmicCalOnly";
    nam[cosmicExtracted]  = "cosmicExtracted";
    nam[cosmicNoField]    = "cosmicNoField";
    nam[cosmic]           = "cosmic";
    nam[bb1]              = "bb1";
    nam[bb2]              = "bb2";
    //nam[] = "";
  }

  return nam;
}
