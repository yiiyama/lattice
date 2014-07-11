#ifndef FieldAction_h
#define FieldAction_h

#include "ActionBase.h"
#include "Field.h"

namespace lattice {

  class FieldAction : public ActionBase {
  public:
    FieldAction(PhysicsBase*);
    ~FieldAction();
  };

}

#endif
