#ifndef Field_h
#define Field_h

#include "FieldBase.h"

namespace lattice {

  class Field : public FieldBase {
  public:
    Field(unsigned, unsigned, unsigned);
    ~Field();
  };

}

#endif
