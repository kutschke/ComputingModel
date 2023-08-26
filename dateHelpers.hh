#ifndef dateHelpers_hh
#define dateHelpers_hh

//
// Helper functions that work around base 1 indexing in TDatime
// and features missing from std::chrono before C++20.
//
// Much of this won't be needed if we rework the date
// management in C++20.
//

#include "TDatime.h"

#include <string>

// Return month of year on the range Jan=0 ... Dec=11.
// TDatime uses Jan=1 ... Dec=12.
uint32_t monthNumber( TDatime const& date );

// Return day of week on the range
// 0 = Sunday, ... 6=Saturday
// Note that TDatime uses 1=Monday ... 7=Sunday
uint32_t dayOfWeek( TDatime const& date );

// This won't be needed in c++20.
bool isLeapYear( uint32_t year );

// Leap year aware days of each month; base 0 indexing for month.
uint32_t daysPerMonth ( uint32_t month, uint32_t year );

// Return 3 letter month abbreviation, base 0 indexing.
std::string monthShortName( uint32_t month);

// Append midnight to a date string
std::string dayStart( std::string const& date);

// Append one second before midnight to a date string
std::string dayEnd( std::string const& date);

// Return date in one of several formats:
// The full format is: "yyyy-mm-dd hh:mm:ss", with the quotes
//  - If hhmmss is false, do not print the hh:mm:ss or the space before it.
//  - If quoted is false, do not print the quotes.
std::string formatDate( TDatime const& t, bool hhmmss=true, bool quoted=true );

#endif
