#ifndef FieldBase_h
#define FieldBase_h

#include "Coordinate.h"

#include "TRandom.h"

#include <map>
#include <set>

namespace lattice {

  class FieldBase {
  public:
    FieldBase();
    virtual ~FieldBase();

    void initialize();
    virtual void randomize(TRandom&, double);
    virtual void trial(Coordinate const&, double);
    virtual void update();
    virtual void clearTrial();

    virtual void setBoundaryCondition(Coordinate const&, double);
    virtual void setBoundaryCondition(Coordinate const* _coord, double _val) { setBoundaryCondition(*_coord, _val); }

    virtual double getVal(Coordinate const&) const;
    virtual double getDerivative(Coordinate const&, unsigned) const;

    virtual Coordinate getCoord(unsigned) const = 0;
    virtual Coordinate* getCoordObject(unsigned _idx) const { return new Coordinate(getCoord(_idx)); }
    bool isFixed(Coordinate const& _coord) const { return fixedPoints_.find(_coord) != fixedPoints_.end(); }

    double getScaleInv(unsigned _iD) const { return scaleInv_[_iD]; }

    typedef std::map<Coordinate, double> ValueMap;
    typedef std::map<Coordinate, double>::const_iterator VMItr;
    typedef std::set<Coordinate> CoordSet;
    typedef std::set<Coordinate>::const_iterator CSIter;

  protected:
    double calculateDerivative_(Coordinate const&, unsigned, double) const;

    ValueMap values_;
    std::vector<ValueMap> derivatives_;

    ValueMap trialValues_;
    std::vector<ValueMap> trialDerivatives_;

    CoordSet fixedPoints_;

    double scaleInv_[Coordinate::MAXDIM];
  };

}

#endif
