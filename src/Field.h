#ifndef Field_h
#define Field_h

#include "FieldBase.h"

namespace lattice {

  class Field : public FieldBase {
  public:
    Field(unsigned, unsigned, unsigned, double);
    ~Field();

    unsigned getNDim() const { return nSpatial_ + 1; }

  private:
    unsigned nSpatial_;
  };

}

#endif
