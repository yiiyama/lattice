#include "ActionBase.h"

namespace lattice {

  ActionBase::ActionBase(PhysicsBase* _obj) :
    obj_(_obj)
  {
  }

  ActionBase::~ActionBase()
  {}

  ActionFactoryStore* ActionFactoryStore::singleton_(0);

  ActionFactoryStore::ActionFactoryStore() :
    store_()
  {
    if(singleton_)
      throw std::runtime_error("ActionFactoryStore instantiated twice");
  }

  /*static*/
  ActionFactoryStore*
  ActionFactoryStore::singleton()
  {
    static ActionFactoryStore store;
    store.singleton_ = &store;
    return &store;
  }

  ActionBase*
  getAction(char const* _name, PhysicsBase* _obj)
  {
    return (*ActionFactoryStore::singleton()->get(_name))(_obj);
  }

}
