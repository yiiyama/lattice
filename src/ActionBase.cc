#include "ActionBase.h"

namespace lattice {

  ActionBase::ActionBase(FieldBase* _obj) :
    obj_(_obj)
  {
    if(!obj_)
      throw std::runtime_error("Null or incompatible object passed to Action");

    obj_->initialize();
  }

  ActionBase::~ActionBase()
  {
  }

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
  getAction(char const* _name, FieldBase* _obj)
  {
    return (*ActionFactoryStore::singleton()->get(_name))(_obj);
  }

}
