#include "../src/ParticleAction.h"
#include "../src/Particle.h"

namespace lattice {
  
  class FreeParticle : public ParticleAction {
  public:
    FreeParticle(FieldBase*);
    ~FreeParticle();

    double dS(Coordinate const&, bool = false) const;
  };

  FreeParticle::FreeParticle(FieldBase* _part) :
    ParticleAction(_part)
  {
  }

  FreeParticle::~FreeParticle()
  {
  }

  double
  FreeParticle::dS(Coordinate const& _coord, bool _trial/* = false*/) const
  {
    // S = sumT 0.5 * dxdt^2

    Particle const& particle(*static_cast<Particle const*>(obj_));
    double v(particle.getDerivative(_coord, _trial));
    return 0.5 * v * v;
  }

  DEFINE_LATTICE_ACTION(FreeParticle);

}
