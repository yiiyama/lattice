#ifndef PhysicsBase_h
#define PhysicsBase_h

#include "Coordinate.h"

#include "TRandom.h"

#include <map>

namespace lattice {

  class PhysicsBase {
  public:
    PhysicsBase();
    virtual ~PhysicsBase();

    virtual void randomize(TRandom&, double);
    virtual void trial(Coordinate const&, double);
    virtual void update();
    virtual void clearTrial();

    virtual double getVal(Coordinate const&) const;
    virtual double getDerivative(Coordinate const&, unsigned) const;

    virtual Coordinate getCoord(unsigned) const = 0;

    typedef std::map<Coordinate, double> ValueMap;
    typedef std::map<Coordinate, double>::const_iterator VMItr;

  protected:
    double calculateDerivative_(Coordinate const&, unsigned, double) const;

    ValueMap values_;
    std::vector<ValueMap> derivatives_;

    ValueMap trialValues_;
    std::vector<ValueMap> trialDerivatives_;

    double scaleInv_[Coordinate::MAXDIM];
  };

}

#endif
