#ifndef RunType_hh
#define RunType_hh
//
// Enum-matched-to-String class for defining run types.
//

#include "EnumToStringSparse.hh"


class RunTypeDetail{
public:

  enum enum_type { unknown, noData, cosmicCalOnly, cosmicExtracted, cosmicNoField, cosmic, bb1, bb2 };

  static std::string const& typeName();

  static std::map<enum_type,std::string> const& names();

};

typedef mu2e::EnumToStringSparse<RunTypeDetail> RunType;

#endif
