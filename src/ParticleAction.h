#ifndef ParticleAction_h
#define ParticleAction_h

#include "ActionBase.h"

namespace lattice {

  class ParticleAction : public ActionBase {
  public:
    ParticleAction(FieldBase*);
    ~ParticleAction();
  };

}

#endif
