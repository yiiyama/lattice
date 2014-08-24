#include "Coordinate.h"

#include <stdexcept>
#include <cmath>
#include <cstdio>

namespace lattice {

  Coordinate::Coordinate()
  {
    set(0, 0, 0);
  }
  
  Coordinate::Coordinate(unsigned _ndim, int const* _coords, int const* _highs)
  {
    set(_ndim, _coords, _highs);
  }

  Coordinate::Coordinate(Coordinate const& _orig)
  {
    set(_orig.ndim_, _orig.coords_, _orig.highs_);
  }

  Coordinate::~Coordinate()
  {
  }

  Coordinate&
  Coordinate::operator=(Coordinate const& _rhs)
  {
    set(_rhs.ndim_, _rhs.coords_, _rhs.highs_);
    return *this;
  }

  void
  Coordinate::set(unsigned _ndim, int const* _coords, int const* _highs)
  {
    ndim_ = _ndim;

    if(ndim_ > MAXDIM)
      throw std::runtime_error("Too many dimensions");

    for(unsigned iD(0); iD != ndim_; ++iD){
      coords_[iD] = _coords[iD];
      highs_[iD] = _highs[iD];
    }
  }

  bool
  Coordinate::isValid() const
  {
    for(unsigned iD(0); iD != ndim_; ++iD)
      if(coords_[iD] < 0 || coords_[iD] > highs_[iD]) return false;
    return true;
  }

  std::string
  Coordinate::getName() const
  {
    std::string name;
    for(unsigned iD(0); iD != ndim_; ++iD){
      if(coords_[iD] > 0) name += "p";
      else if(coords_[iD] < 0) name += "m";
      char val[100];
      unsigned absval(std::abs(coords_[iD]));
      std::sprintf(val, "%d", absval);
      name += val;
      if(iD != ndim_ - 1) name += "_";
    }

    return name;
  }

  Coordinate&
  Coordinate::next()
  {
    unsigned iD(0);
    for(; iD != ndim_ - 1; ++iD){
      if(coords_[iD] < highs_[iD]){
        ++coords_[iD];
        break;
      }
      else
        coords_[iD] = 0;
    }
    if(iD == ndim_ - 1) ++coords_[iD];

    return *this;
  }

  Coordinate&
  Coordinate::prev()
  {
    unsigned iD(0);
    for(; iD != ndim_ - 1; ++iD){
      if(coords_[iD] > 0){
        --coords_[iD];
        break;
      }
      else
        coords_[iD] = highs_[iD];
    }
    if(iD == ndim_ - 1) --coords_[iD];

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
    return coords_[_iD] == highs_[_iD];
  }

  bool
  Coordinate::operator<(Coordinate const& _rhs) const
  {
    if(ndim_ != _rhs.ndim_)
      throw std::runtime_error("Comparison between incompatible coordinates");

    unsigned iD(ndim_ - 1);
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
    if(ndim_ != _rhs.ndim_)
      throw std::runtime_error("Comparison between incompatible coordinates");

    for(unsigned iD(0); iD != ndim_; ++iD)
      if(coords_[iD] != _rhs.coords_[iD]) return false;

    return true;
  }
    
}
