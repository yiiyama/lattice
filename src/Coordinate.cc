#include "Coordinate.h"

#include <stdexcept>
#include <cmath>
#include <cstdio>

namespace lattice {
  
  Coordinate::Coordinate(Bounds const& _bounds) :
    bounds_(&_bounds)
  {
    std::fill_n(coords_, MAXDIM, 0);
  }

  Coordinate::Coordinate(Coordinate const& _orig) :
    bounds_(_orig.bounds_)
  {
    for(unsigned iD(0); iD != bounds_->ndim; ++iD)
      coords_[iD] = _orig.coords_[iD];
  }

  Coordinate::~Coordinate()
  {
  }

  Coordinate&
  Coordinate::operator=(Coordinate const& _rhs)
  {
    bounds_ = _rhs.bounds_;
    for(unsigned iD(0); iD != bounds_->ndim; ++iD)
      coords_[iD] = _rhs.coords_[iD];

    return *this;
  }

  bool
  Coordinate::isValid() const
  {
    for(unsigned iD(0); iD != bounds_->ndim; ++iD)
      if(coords_[iD] < 0 || coords_[iD] > bounds_->max[iD]) return false;
    return true;
  }

  std::string
  Coordinate::getName() const
  {
    std::string name;
    for(unsigned iD(0); iD != bounds_->ndim; ++iD){
      char val[100];
      std::sprintf(val, "%d", coords_[iD]);
      name += val;
      if(iD != bounds_->ndim - 1) name += "_";
    }

    return name;
  }

  Coordinate&
  Coordinate::next()
  {
    unsigned iD(0);
    for(; iD != bounds_->ndim - 1; ++iD){
      if(coords_[iD] < bounds_->max[iD]){
        ++coords_[iD];
        break;
      }
      else
        coords_[iD] = 0;
    }
    if(iD == bounds_->ndim - 1) ++coords_[iD];

    return *this;
  }

  Coordinate&
  Coordinate::prev()
  {
    unsigned iD(0);
    for(; iD != bounds_->ndim - 1; ++iD){
      if(coords_[iD] > 0){
        --coords_[iD];
        break;
      }
      else
        coords_[iD] = bounds_->max[iD];
    }
    if(iD == bounds_->ndim - 1) --coords_[iD];

    return *this;
  }

  Coordinate&
  Coordinate::move(char _axis, int _d)
  {
    switch(_axis){
    case 't':
      coords_[0] += _d;
      break;
    case 'x':
      coords_[1] += _d;
      break;
    case 'y':
      coords_[2] += _d;
      break;
    case 'z':
      coords_[3] += _d;
      break;
    default:
      throw std::runtime_error("Invalid axis label");
    }

    return *this;
  }

  Coordinate&
  Coordinate::move(unsigned _axis, int _d)
  {
    coords_[_axis] += _d;
    
    return *this;
  }

  Coordinate&
  Coordinate::moveTo(int _t, int _x/* = 0*/, int _y/* = 0*/, int _z/* = 0*/)
  {
    coords_[0] = _t;
    coords_[1] = _x;
    coords_[2] = _y;
    coords_[3] = _z;

    return *this;
  }

  bool
  Coordinate::atLowEdge(unsigned _iD) const
  {
    return coords_[_iD] == 0;
  }

  bool
  Coordinate::atHighEdge(unsigned _iD) const
  {
    return coords_[_iD] == bounds_->max[_iD];
  }

  bool
  Coordinate::operator<(Coordinate const& _rhs) const
  {
    if(bounds_->ndim != _rhs.bounds_->ndim)
      throw std::runtime_error("Comparison between incompatible coordinates");

    unsigned iD(bounds_->ndim - 1);
    while(true){
      if(coords_[iD] < _rhs.coords_[iD]) return true;
      if(coords_[iD] > _rhs.coords_[iD]) return false;
      if(iD == 0) break;
      --iD;
    }
    
    return false;
  }

  bool
  Coordinate::operator==(Coordinate const& _rhs) const
  {
    if(bounds_->ndim != _rhs.bounds_->ndim)
      throw std::runtime_error("Comparison between incompatible coordinates");

    for(unsigned iD(0); iD != bounds_->ndim; ++iD)
      if(coords_[iD] != _rhs.coords_[iD]) return false;

    return true;
  }
    
}
