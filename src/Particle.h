#ifndef Particle_h
#define Particle_h

#include "FieldBase.h"

#include <vector>

namespace lattice {

  class Particle : public FieldBase {
  public:
    Particle(unsigned, unsigned, double);
    ~Particle();

    double getDerivative(Coordinate const&, unsigned) const;

    Coordinate getCoord(unsigned) const;

  private:
    unsigned nT_;
    unsigned nD_;
  };

}

#endif
