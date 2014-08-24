#include "ParticleAction.h"
#include "Particle.h"

#include <stdexcept>

namespace lattice {
  
  ParticleAction::ParticleAction(FieldBase* _obj) :
    ActionBase(dynamic_cast<Particle*>(_obj))
  {
  }

  ParticleAction::~ParticleAction()
  {
  }

}
