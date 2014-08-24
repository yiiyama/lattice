#ifndef Particle_h
#define Particle_h

#include "FieldBase.h"

#include <vector>

namespace lattice {

  class Particle : public FieldBase {
  public:
    Particle(unsigned, unsigned, double);
    ~Particle();

    double getDerivative(Coordinate const& _coord, unsigned, bool _trial = false) const { return FieldBase::getDerivative(_coord, 0, _trial); }
    double getDerivative(Coordinate const& _coord, bool _trial = false) const { return FieldBase::getDerivative(_coord, 0, _trial); }
  };

}

#endif
