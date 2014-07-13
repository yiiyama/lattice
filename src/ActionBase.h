#ifndef ActionBase_h
#define ActionBase_h

#include "FieldBase.h"

#include <map>
#include <string>
#include <stdexcept>

namespace lattice {
  
  class ActionBase {
  public:
    ActionBase(FieldBase*);
    virtual ~ActionBase();

    FieldBase* getObj() const { return obj_; }
    virtual double eval() const = 0;

    virtual void setParameter(unsigned, double) {}

  protected:
    FieldBase* obj_;
  };

  class ActionFactoryStore {
  public:
    struct FactoryBase {
      virtual ActionBase* operator()(FieldBase*) const = 0;
    };

    template<typename L>
    struct Factory : public FactoryBase {
      Factory(std::string const& _name)
      {
        ActionFactoryStore::singleton()->registerFactory(_name, this);
      }
      ActionBase* operator()(FieldBase* _obj) const
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

  ActionBase* getAction(char const*, FieldBase*);
}

#define DEFINE_ACTION(TYPE) \
  ActionFactoryStore::Factory<TYPE> lattice##TYPE##Factory(#TYPE)

#endif
