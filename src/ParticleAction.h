#ifndef ParticleAction_h
#define ParticleAction_h

#include "ActionBase.h"
#include "Particle.h"

namespace lattice {

  class ParticleAction : public ActionBase {
  public:
    ParticleAction(FieldBase*);
    ~ParticleAction();

  protected:
    Particle* particle_;
  };

}

#endif
