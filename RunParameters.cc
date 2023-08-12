#include "RunParameters.hh"

RunParameters::RunParameters(){
}

RunParameters::RunParameters( Config const& conf):
  _eventSize(conf.eventSize()),
  _eventsPerDay(conf.eventsPerDay()),
  _triggerRejection(conf.triggerRejection()),
  _comment(conf.comment()),
  _type(RunType( conf.type()))
{
}

std::ostream& operator<<(std::ostream& os, const RunParameters& r ){
  os << "Type: "                << r.type()
     << "  Event size: "        << r.eventSize()
     << "  Events per day: "    << r.eventsPerDay()
     << "  Trigger rejection: " << r.triggerRejection();
  if ( !r.comment().empty() ){
    os << "\n        " << r.comment();
  }
  return os;
}
