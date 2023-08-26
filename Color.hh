#ifndef Color_hh
#define Color_hh
//
// Enum-matched-to-String class for defining colors.
//

#include "EnumToStringSparse.hh"

#include "Rtypes.h"

class ColorDetail{
public:

  enum enum_type { unknown=-1,
                   white=EColor::kWhite, black=EColor::kBlack, gray=EColor::kGray, red=EColor::kRed, blue=EColor::kBlue   };

  //enum EColor { kWhite =0,   kBlack =1,   kGray=920,
  //            kRed   =632, kGreen =416, kBlue=600, kYellow=400, kMagenta=616, kCyan=432,
  //            kOrange=800, kSpring=820, kTeal=840, kAzure =860, kViolet =880, kPink=900 };

  static std::string const& typeName();

  static std::map<enum_type,std::string> const& names();

};

typedef mu2e::EnumToStringSparse<ColorDetail> Color;

#endif


