#include "dateHelpers.hh"

#include <array>

uint32_t monthNumber( TDatime const& date ){
  return date.GetMonth()-1;
}
uint32_t dayOfWeek( TDatime const& date ){
  auto i = date.GetDayOfWeek();
  return ( i==7 ) ? 0 :i;
}

bool isLeapYear( uint32_t y ){
  if ( y % 400 == 0 ) { return true; }
  if ( y % 100 == 0 ) { return false; }
  if ( y %   4 == 0 ) { return true; }
  return false;
}

uint32_t daysPerMonth ( uint32_t month, uint32_t year ){
  static const std::array<uint32_t,12>  _normal{31,28,31,30,31,30,31,31,30,31,30,31};
  static const std::array<uint32_t,12>  _leap{31,29,31,30,31,30,31,31,30,31,30,31};
  if ( isLeapYear( year ) ){
    return _leap.at(month);
  }
  return _normal.at(month);
}

std::string monthShortName ( uint32_t m ){
  static std::array<std::string,12> names{"Jan", "Feb", "Mar", "Apr", "May", "Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
  return names.at(m);
}
