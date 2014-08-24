#include "Field.h"

namespace lattice {

  Field::Field(unsigned _spatialDim, unsigned _nT, unsigned _nX, double _dxdt) :
    FieldBase(_nT, _nX, _dxdt),
    nSpatial_(_spatialDim)
  {
    if(nSpatial_ > Coordinate::MAXDIM - 1)
      throw std::runtime_error("Too many dimensions");

    int init[Coordinate::MAXDIM];
    int highs[Coordinate::MAXDIM];
    init[0] = 0;
    highs[0] = nT_;
    for(unsigned iD(0); iD != nSpatial_; ++iD){
      init[iD + 1] = 0;
      highs[iD + 1] = nX_;
    }
    firstCoord_.set(nSpatial_ + 1, init, highs);

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
