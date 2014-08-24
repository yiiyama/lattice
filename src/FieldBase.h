#ifndef FieldBase_h
#define FieldBase_h

#include "Coordinate.h"

#include "TRandom.h"

#include <vector>

namespace lattice {

  class FieldBase {
  public:
    FieldBase(unsigned, unsigned, double);
    virtual ~FieldBase();

    void initialize();
    virtual void randomize(TRandom&, double);
    virtual void trial(Coordinate const&, double);
    virtual void update();
    virtual void clearTrial();

    virtual void setBoundaryCondition(Coordinate const&, double);
    virtual void setBoundaryCondition(Coordinate const* _coord, double _val) { setBoundaryCondition(*_coord, _val); }

    // If second argument is true, first look in trial ValueMaps. If not found, defaults back to set values
    virtual double getVal(Coordinate const&, bool = false) const;
    virtual double getDerivative(Coordinate const&, unsigned, bool = false) const;

    virtual CoordSet getTrialCoordinates() const;

    virtual Coordinate const& getCoord() const { return firstCoord_; }
    virtual Coordinate* getCoordObject() const { return new Coordinate(firstCoord_); }
    bool isFixed(Coordinate const& _coord) const { return fixedPoints_.find(_coord) != fixedPoints_.end(); }

    double getDxdt() const { return dxdt_; }

  protected:
    // uses trial values
    double calculateDerivative_(Coordinate const&, unsigned) const;

    unsigned nT_;
    unsigned nX_;
    double dxdt_;

    ValueMap values_;
    std::vector<ValueMap> derivatives_;

    ValueMap trialValues_;
    std::vector<ValueMap> trialDerivatives_;

    Bounds bounds_;
    Coordinate firstCoord_;

    CoordSet fixedPoints_;
  };

}

#endif
