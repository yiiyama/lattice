#include "../src/ParticleAction.h"

namespace lattice {
  
  class HarmonicOscillator : public ParticleAction {
  public:
    HarmonicOscillator(FieldBase*);
    ~HarmonicOscillator();

    double eval() const;

    void setParameter(unsigned, double _p) { omegaDt_ = _p; }

  private:
    double omegaDt_;
  };

  HarmonicOscillator::HarmonicOscillator(FieldBase* _part) :
    ParticleAction(_part),
    omegaDt_(1.)
  {
  }

  HarmonicOscillator::~HarmonicOscillator()
  {
  }

  double
  HarmonicOscillator::eval() const
  {
    // S = sumT [0.5 * dxdt^2 + 0.5 * omega^2 x^2]
    double S(0.);
    for(Coordinate coord(particle_->getCoord(0)); coord.isValid(); coord.next()){
      double omegaX(particle_->getVal(coord) * omegaDt_ * particle_->getScaleInv(0));
      S += omegaX * omegaX;
      double dxdt(particle_->getDerivative(coord, 0));
      S += dxdt * dxdt;
    }

    return 0.5 * S;
  }

  DEFINE_ACTION(HarmonicOscillator);

}
