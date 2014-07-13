#include "FieldAction.h"

namespace lattice {
  
  FieldAction::FieldAction(FieldBase* _obj) :
    ActionBase(dynamic_cast<Field*>(_obj))
  {
    if(!_obj)
      throw std::runtime_error("Non-field object passed to field action");
  }

  FieldAction::~FieldAction()
  {
  }

}
