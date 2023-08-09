#include "Run.hh"

#include <iostream>

Run::Run(){
}

std::ostream& operator<<(std::ostream& os, const Run& r ){
  os << r.type();
  return os;
}
