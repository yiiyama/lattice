#ifndef ActionBase_h
#define ActionBase_h

#include "PhysicsBase.h"

#include <map>
#include <string>
#include <stdexcept>

namespace lattice {
  
  class ActionBase {
  public:
    ActionBase(PhysicsBase*);
    virtual ~ActionBase();

    PhysicsBase* getObj() const { return obj_; }
    virtual double eval() const = 0;

    virtual void setParameter(unsigned, double) {}

  protected:
    PhysicsBase* obj_;
  };

  class ActionFactoryStore {
  public:
    struct FactoryBase {
      virtual ActionBase* operator()(PhysicsBase*) const = 0;
    };

    template<typename L>
    struct Factory : public FactoryBase {
      Factory(std::string const& _name)
      {
        ActionFactoryStore::singleton()->registerFactory(_name, this);
      }
      ActionBase* operator()(PhysicsBase* _obj) const
      {
        return new L(_obj);
      }
    };

    ActionFactoryStore();

    void registerFactory(std::string const& _name, const FactoryBase* _factory)
    {
      store_[_name] = _factory;
    }

    const FactoryBase* get(std::string const& _name) const
    {
      std::map<std::string, const FactoryBase*>::const_iterator fItr(store_.find(_name));
      if(fItr == store_.end())
        throw std::runtime_error("Action " + _name + " not registered");
      return fItr->second;
    }

    static ActionFactoryStore* singleton();

  private:
    static ActionFactoryStore* singleton_;

    std::map<std::string, const FactoryBase*> store_;
  };

  ActionBase* getAction(char const*, PhysicsBase*);
}

#define DEFINE_ACTION(TYPE) \
  ActionFactoryStore::Factory<TYPE> lattice##TYPE##Factory(#TYPE)

#endif
