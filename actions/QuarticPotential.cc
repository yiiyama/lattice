#include "../src/FieldAction.h"

namespace lattice {

  class QuarticPotential : public FieldAction {
  public:
    QuarticPotential(FieldBase*);
    ~QuarticPotential();

    double eval() const;

    void setParameter(unsigned, double);

  private:
    double mu2_;
    double lambda_;
  };

  QuarticPotential::QuarticPotential(FieldBase* _field) :
    FieldAction(_field),
    mu2_(-1.),
    lambda_(1.)
  {
  }

}
