#include "FieldBase.h"

#include <stdexcept>

namespace lattice {

  FieldBase::FieldBase(unsigned _nT, unsigned _nX, double _dxdt) :
    nT_(_nT),
    nX_(_nX),
    dxdt_(_dxdt),
    values_(),
    derivatives_(),
    trialValues_(),
    trialDerivatives_(),
    firstCoord_(),
    fixedPoints_()
  {
  }

  FieldBase::~FieldBase()
  {
  }

  void
  FieldBase::initialize()
  {
    values_.clear();
    for(unsigned iD(0); iD != derivatives_.size(); ++iD)
      derivatives_[iD].clear();
    
    for(Coordinate coord(firstCoord_); coord.isValid(); coord.next()){
      values_[coord] = 0.;
      for(unsigned iD(0); iD != derivatives_.size(); ++iD)
        derivatives_[iD][coord] = 0.;
    }

    clearTrial();

    fixedPoints_.clear();
  }

  void
  FieldBase::randomize(TRandom& _rand, double _df)
  {
    clearTrial();

    for(Coordinate coord(firstCoord_); coord.isValid(); coord.next())
      if(!isFixed(coord)) values_[coord] = _rand.Uniform(-_df, _df);

    for(Coordinate coord(firstCoord_); coord.isValid(); coord.next()){
      for(unsigned iD(0); iD != derivatives_.size(); ++iD)
        derivatives_[iD][coord] = calculateDerivative_(coord, iD);
    }
  }

  void
  FieldBase::trial(Coordinate const& _coord, double _value)
  {
    trialValues_[_coord] = _value;
    for(unsigned iD(0); iD != derivatives_.size(); ++iD){
      Coordinate coord(_coord);
      coord.move(iD, -1);
      for(unsigned iX(0); iX != 3; ++iX){
        trialDerivatives_[iD][coord] = calculateDerivative_(coord, iD);
        coord.move(iD, +1);
      }
    }
  }

  void
  FieldBase::update()
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
  FieldBase::clearTrial()
  {
    trialValues_.clear();
    for(unsigned iD(0); iD != trialDerivatives_.size(); ++iD)
      trialDerivatives_[iD].clear();
  }

  void
  FieldBase::setBoundaryCondition(Coordinate const& _coord, double _value)
  {
    values_[_coord] = _value;
    fixedPoints_.insert(_coord);
  }

  double
  FieldBase::getVal(Coordinate const& _coord) const
  {
    VMItr vItr(trialValues_.find(_coord));
    if(vItr != trialValues_.end()) return vItr->second;
    
    vItr = values_.find(_coord);
    if(vItr == values_.end())
      throw std::runtime_error(("Invalid coordinate " + _coord.getName()).c_str());

    return vItr->second;
  }

  double
  FieldBase::getDerivative(Coordinate const& _coord, unsigned _iD) const
  {
    VMItr vItr(trialDerivatives_[_iD].find(_coord));
    if(vItr != trialDerivatives_[_iD].end()) return vItr->second;

    vItr = derivatives_[_iD].find(_coord);
    if(vItr == derivatives_[_iD].end())
      throw std::runtime_error(("Invalid coordinate" + _coord.getName()).c_str());

    return vItr->second;
  }

  double
  FieldBase::calculateDerivative_(Coordinate const& _coord, unsigned _iD) const
  {
    double deriv(0.);
    
    Coordinate coord(_coord);
    if(coord.atLowEdge(_iD)){
      double v(getVal(coord));
      double vplus(getVal(coord.move(_iD, 1)));
      deriv = (vplus - v);
    }
    else if(coord.atHighEdge(_iD)){
      double v(getVal(coord));
      double vminus(getVal(coord.move(_iD, -1)));
      deriv = (v - vminus);
    }
    else{
      double vplus(getVal(coord.move(_iD, 1)));
      double vminus(getVal(coord.move(_iD, -2)));
      deriv = (vplus - vminus) * 0.5;
    }

    if(_iD == 0) deriv *= dxdt_;

    return deriv;
  }

}
