#ifndef BB2_hh
#define BB2_hh

class BB2 {

public:

  static constexpr double t_spill           = 0.0431; // Duration of one slow spill (s)
  static constexpr double nSpillsPerMICycle = 8;      // Number of spills in one MI cycle

  BB2();

  int status() const { return _status;}

private:
  int _status = 0;
};

#endif
