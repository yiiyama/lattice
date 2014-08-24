#ifndef Main_h
#define Main_h

#include "ActionBase.h"

#include <string>

namespace lattice {

  class LatticeSimulation {
  public:
    LatticeSimulation(ActionBase*);
    ~LatticeSimulation();

    void run();

    void setNSweeps(unsigned _n) { nSweeps_ = _n; }
    void setThermalizationWait(unsigned _n) { nTherm_ = _n; }
    void setFillInterval(unsigned _n) { fillInterval_ = _n; }
    void setFluctuationSize(double _d) { df_ = _d; }
    void setOutputName(char const* _name) { outputName_ = _name; }
    void setSeed(int _s) { seed_ = _s; }

  private:
    ActionBase* action_;

    unsigned nSweeps_;
    unsigned nTherm_;
    unsigned fillInterval_;
    double df_;
    std::string outputName_;
    int seed_;
  };

}

#endif
