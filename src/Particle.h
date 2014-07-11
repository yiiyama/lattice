#ifndef Particle_h
#define Particle_h

#include "PhysicsBase.h"

#include <vector>

namespace lattice {

  class Particle : public PhysicsBase {
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
