#ifndef Constants_hh
#define Constants_hh

namespace constants {
  constexpr double   kBToMB        = 1.E-3;
  constexpr double   kBToGB        = 1.E-6;
  constexpr double   kBToTB        = 1.E-9;
  constexpr double   kBToPB        = 1.E-12;
  constexpr double   MBTokB        = 1.E3;
  constexpr double   GBTokB        = 1.E6;
  constexpr double   TBTokB        = 1.E9;
  constexpr double   PBTokB        = 1.E12;

  constexpr unsigned secondsPerHour =  3600;
  constexpr unsigned hoursPerDay    =    24;
  constexpr unsigned daysPerWeek    =     7;
  constexpr unsigned secondsPerDay  =  secondsPerHour*hoursPerDay;
  constexpr unsigned secondsPerWeek =  secondsPerHour*hoursPerDay*daysPerWeek;

}

#endif
