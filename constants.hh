#ifndef Constants_hh
#define Constants_hh

namespace constants {
  constexpr unsigned secondsPerHour =  3600;
  constexpr unsigned hoursPerDay    =    24;
  constexpr unsigned daysPerWeek    =     7;
  constexpr unsigned secondsPerDay  =  secondsPerHour*hoursPerDay;
  constexpr unsigned secondsPerWeek =  secondsPerHour*hoursPerDay*daysPerWeek;
}

#endif
