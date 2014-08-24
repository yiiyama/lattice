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
    Particle const& particle(*static_cast<Particle const*>(obj_));
    
    // S = sumT [0.5 * dxdt^2 + 0.5 * omega^2 x^2]
    double S(0.);
    for(Coordinate coord(particle.getCoord()); coord.isValid(); coord.next()){
      double omegaX(particle.getVal(coord) * omegaDt_ * particle.getDxdt());
      S += omegaX * omegaX;
      double dxdt(particle.getDerivative(coord, 0));
      S += dxdt * dxdt;
    }

    return 0.5 * S;
  }

  DEFINE_ACTION(HarmonicOscillator);

}
