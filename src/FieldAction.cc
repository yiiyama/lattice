#include "FieldAction.h"

namespace lattice {
  
  FieldAction::FieldAction(FieldBase* _obj) :
    ActionBase(dynamic_cast<Field*>(_obj))
  {
  }

  FieldAction::~FieldAction()
  {
  }

}
