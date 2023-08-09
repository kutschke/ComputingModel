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
    nam[unknown]    = "unknown";
    nam[CosmicExtracted]     = "CosmicExtracted";
    nam[CosmicNoField] = "CosmicNoField";
    nam[Cosmic] = "Cosmic";
    nam[BB1] = "BB1";
    nam[BB2] = "BB2";
      //nam[] = "";
  }

  return nam;
}
