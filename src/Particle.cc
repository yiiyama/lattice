#include "Particle.h"

#include <stdexcept>

namespace lattice {

  Particle::Particle(unsigned _nT, unsigned _nX, double _dxdt) :
    FieldBase(_nT, _nX, _dxdt)
  {
    // Dimension in Particle is used in a different sense from dimension in field.
    // Coordinate object will only have time and one "spatial" dimension.
    // The latter is simply an n-valued (0, 1, 2, ..) index for the spatial axis
    // Nevertheless we require the same maximum dimensions as in the case for fields, just for convenience.
    if(nX_ > MAXDIM - 1)
      throw std::runtime_error("Too many dimensions");

    bounds_.ndim = 2;
    bounds_.max[0] = nT_ - 1;
    bounds_.max[1] = nX_ - 1;
    
    derivatives_.resize(1);
    trialDerivatives_.resize(1);

    for(Coordinate coord(firstCoord_); coord.isValid(); coord.next()){
      values_[coord] = 0.;
      derivatives_[0][coord] = 0.;
    }
  }

  Particle::~Particle()
  {
  }

}
