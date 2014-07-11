#ifndef Field_h
#define Field_h

#include "PhysicsBase.h"

namespace lattice {

  class Field : public PhysicsBase {
  public:
    Field(unsigned, unsigned, unsigned);
    ~Field();
  };

}

#endif
