//
// Enum-matched-to-String class for defining data types.
//

#include "DataType.hh"

std::string const& DataTypeDetail::typeName() {
  static std::string type("DataType");
  return type;
}

std::map<DataTypeDetail::enum_type,std::string> const& DataTypeDetail::names(){

  static std::map<enum_type,std::string> nam;

  if ( nam.empty() ){
    nam[unknown]            = "unknown";
    nam[bb1OnSpill]         = "bb1OnSpill";
    nam[bb2OnSpill]         = "bb2OnSpill";
    nam[intensityStream]    = "intensityStream";
    nam[extMonPixelSummary] = "extMonPixelSummary";
    nam[extMonPrescale]     = "extMonPrescale";
    nam[extMonAFFSummary]   = "extMonAFFSummary";
    nam[extMonAFFPrescale]  = "extMonAFFPrescale";
    nam[offSpill]           = "offSpill";
    nam[crvPedestal]        = "crvPedestal";
    nam[caloPulser]         = "caloPulser";
    nam[stmSummary]         = "stmSummary";
    nam[stmWaveforms]       = "stmWaveforms";
    nam[stmPrescaled]       = "stmPrescaled";
    nam[debug]              = "debug";
    //nam[] = "";
  }

  return nam;
}
