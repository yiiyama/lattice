#include "Particle.h"

#include <stdexcept>

namespace lattice {

  Particle::Particle(unsigned _nT, unsigned _nD, double _dt) :
    nT_(_nT),
    nD_(_nD)
  {
    // Dimension in Particle is used in a different sense from dimension in field.
    // Coordinate object will only have time and one "spatial" dimension.
    // The latter is simply a n-valued (0, 1, 2, ..) index for the spatial axis
    // Nevertheless we require the same maximum dimensions as in the case for fields, just for convenience.
    if(nD_ > Coordinate::MAXDIM - 1)
      throw std::runtime_error("Too many dimensions");

    derivatives_.resize(1);
    trialDerivatives_.resize(1);

    for(Coordinate coord(getCoord(0)); coord.isValid(); coord.next()){
      values_[coord] = 0.;
      derivatives_[0][coord] = 0.;
    }

    scaleInv_[0] = 1. / _dt;
  }

  Particle::~Particle()
  {
  }

  double
  Particle::getDerivative(Coordinate const& _coord, unsigned) const
  {
    return PhysicsBase::getDerivative(_coord, 0);
  }

  Coordinate
  Particle::getCoord(unsigned _index) const
  {
    int lows[2] = {0, 0};
    int highs[2];
    highs[0] = nT_ - 1;
    highs[1] = nD_ - 1;

    Coordinate coord(2, lows, lows, highs);
    for(unsigned i(0); i != _index; ++i) coord.next();
    return coord;
  }

}
