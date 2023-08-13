#ifndef DataType_hh
#define DataType_hh
//
// Enum-matched-to-String class for defining data types.
//

#include "EnumToStringSparse.hh"


class DataTypeDetail{
public:

  enum enum_type { unknown,            //
                   bb1OnSpiil,         //
                   bb2OnSpill,         //
                   intensityStream,    //
                   extMonPixelSummary, //
                   extMonPrescale,     //
                   extMonAFFSummary,   //
                   extMonAFFPrescale,  //
                   offSpill,           //
                   crvPedestal,        //
                   caloPulser,         //
                   stmSummary,         //
                   stmWaveforms,       //
                   stmPrescaled,       //
                   debug               //
  };

  static std::string const& typeName();

  static std::map<enum_type,std::string> const& names();

};

typedef mu2e::EnumToStringSparse<DataTypeDetail> DataType;

#endif
