#include "PhysicsBase.h"

#include <stdexcept>

namespace lattice {

  PhysicsBase::PhysicsBase() :
    values_(),
    derivatives_(),
    trialValues_(),
    trialDerivatives_()
  {
    std::fill_n(scaleInv_, Coordinate::MAXDIM, 1.);
  }

  PhysicsBase::~PhysicsBase()
  {
  }

  void
  PhysicsBase::randomize(TRandom& _rand, double _df)
  {
    clearTrial();

    for(Coordinate coord(getCoord(0)); coord.isValid(); ++coord)
      values_[coord] = _rand.Uniform(-_df, _df);

    for(Coordinate coord(getCoord(0)); coord.isValid(); ++coord){
      for(unsigned iD(0); iD != derivatives_.size(); ++iD)
        derivatives_[iD][coord] = calculateDerivative_(coord, iD, scaleInv_[iD]);
    }
  }

  void
  PhysicsBase::trial(Coordinate const& _coord, double _value)
  {
    trialValues_[_coord] = _value;
    for(unsigned iD(0); iD != derivatives_.size(); ++iD){
      Coordinate coord(_coord);
      coord.move(iD, -1);
      for(unsigned iX(0); iX != 3; ++iX){
        trialDerivatives_[iD][coord] = calculateDerivative_(coord, iD, scaleInv_[iD]);
        coord.move(iD, +1);
      }
    }
  }

  void
  PhysicsBase::update()
  {
    for(VMItr vItr(trialValues_.begin()); vItr != trialValues_.end(); ++vItr)
      values_[vItr->first] = vItr->second;
    for(unsigned iD(0); iD != derivatives_.size(); ++iD){
      for(VMItr vItr(trialDerivatives_[iD].begin()); vItr != trialDerivatives_[iD].end(); ++vItr)
        derivatives_[iD][vItr->first] = vItr->second;
    }

    clearTrial();
  }

  void
  PhysicsBase::clearTrial()
  {
    trialValues_.clear();
    for(unsigned iD(0); iD != trialDerivatives_.size(); ++iD)
      trialDerivatives_[iD].clear();
  }

  double
  PhysicsBase::getVal(Coordinate const& _coord) const
  {
    VMItr vItr(trialValues_.find(_coord));
    if(vItr != trialValues_.end()) return vItr->second;
    
    vItr = values_.find(_coord);
    if(vItr == values_.end())
      throw std::runtime_error("Invalid coordinate");

    return vItr->second;
  }

  double
  PhysicsBase::getDerivative(Coordinate const& _coord, unsigned _iD) const
  {
    VMItr vItr(trialDerivatives_[_iD].find(_coord));
    if(vItr != trialDerivatives_[_iD].end()) return vItr->second;

    vItr = derivatives_[_iD].find(_coord);
    if(vItr == derivatives_[_iD].end())
      throw std::runtime_error("Invalid coordinate");

    return vItr->second;
  }

  double
  PhysicsBase::calculateDerivative_(Coordinate const& _coord, unsigned _iD, double _dxinv) const
  {
    Coordinate coord(_coord);
    double xplus(getVal(coord.move(_iD, 1)));
    double xminus(getVal(coord.move(_iD, -2)));
    return (xplus - xminus) * 0.5 * _dxinv;
  }

}
