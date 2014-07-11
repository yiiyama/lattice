#include "ParticleAction.h"

#include <stdexcept>

namespace lattice {
  
  ParticleAction::ParticleAction(PhysicsBase* _obj) :
    ActionBase(_obj),
    particle_(dynamic_cast<Particle*>(_obj))
  {
    if(!_obj)
      throw std::runtime_error("Non-particle object passed to particle action");
  }

  ParticleAction::~ParticleAction()
  {
  }

}
