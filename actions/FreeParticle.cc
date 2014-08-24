#include "../src/ParticleAction.h"

namespace lattice {
  
  class FreeParticle : public ParticleAction {
  public:
    FreeParticle(FieldBase*);
    ~FreeParticle();

    double eval() const;
  };

  FreeParticle::FreeParticle(FieldBase* _part) :
    ParticleAction(_part)
  {
  }

  FreeParticle::~FreeParticle()
  {
  }

  double
  FreeParticle::eval() const
  {
    Particle const& particle(*static_cast<Particle const*>(obj_));
    
    // S = sumT 0.5 * dxdt^2
    double S(0.);
    for(Coordinate coord(particle.getCoord()); coord.isValid(); coord.next()){
      double dxdt(particle.getDerivative(coord, 0));
      S += dxdt * dxdt;
    }

    return 0.5 * S;
  }

  DEFINE_ACTION(FreeParticle);

}
