#ifndef RunType_hh
#define RunType_hh
//
// Enum-matched-to-String class for defining run types.
//

#include "EnumToStringSparse.hh"


class RunTypeDetail{
public:

  enum enum_type { unknown, bb1, bb2, cosmic, cosmicNoField, cosmicExtracted, cosmicCalOnly, noData };

  static std::string const& typeName();

  static std::map<enum_type,std::string> const& names();

};

typedef mu2e::EnumToStringSparse<RunTypeDetail> RunType;

#endif
