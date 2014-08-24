#include "../src/ParticleAction.h"
#include "../src/Particle.h"

namespace lattice {
  
  class HarmonicOscillator : public ParticleAction {
  public:
    HarmonicOscillator(FieldBase*);
    ~HarmonicOscillator();

    double dS(Coordinate const&, bool = false) const;

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
  HarmonicOscillator::dS(Coordinate const& _coord, bool _trial/* = false*/) const
  {
    // S = sumT [0.5 * v^2 + 0.5 * omega^2 x^2]

    Particle const& particle(*static_cast<Particle const*>(obj_));

    double v(particle.getDerivative(_coord, _trial));
    double omegaX(particle.getVal(_coord, _trial) * omegaDt_ * particle.getDxdt());
    return 0.5 * v * v + 0.5 * omegaX * omegaX;
  }

  DEFINE_LATTICE_ACTION(HarmonicOscillator);

}
