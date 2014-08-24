#include "Field.h"

#include <stdexcept>
#include <cstdio>

namespace lattice {

  Field::Field(unsigned _spatialDim, unsigned _nT, unsigned _nX, double _dxdt) :
    FieldBase(_nT, _nX, _dxdt),
    nSpatial_(_spatialDim)
  {
    if(nSpatial_ > MAXDIM - 1)
      throw std::runtime_error("Too many dimensions");

    bounds_.ndim = nSpatial_ + 1;
    bounds_.max[0] = nT_ - 1;
    std::fill_n(bounds_.max + 1, nSpatial_, nX_ - 1);

    derivatives_.resize(nSpatial_ + 1);
    trialDerivatives_.resize(nSpatial_ + 1);

    for(Coordinate coord(firstCoord_); coord.isValid(); coord.next()){
      values_[coord] = 0.;
      for(unsigned iD(0); iD != nSpatial_ + 1; ++iD)
        derivatives_[iD][coord] = 0.;
    }
  }

  Field::~Field()
  {
  }

}
