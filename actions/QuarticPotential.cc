#include "../src/FieldAction.h"
#include "../src/Field.h"

namespace lattice {

  class QuarticPotential : public FieldAction {
  public:
    QuarticPotential(FieldBase*);
    ~QuarticPotential();

    double dS(Coordinate const&, bool = false) const;

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

  QuarticPotential::~QuarticPotential()
  {
  }

  double
  QuarticPotential::dS(Coordinate const& _coord, bool _trial/* = false*/) const
  {
    // L = 0.5 * dphi^2 - 0.5 * mu2 * phi^2 - lambda * phi^4

    Field const& field(*static_cast<Field const*>(obj_));

    double phi(field.getVal(_coord, _trial));
    double phi2(phi * phi);
    double sumDphi2(0.);
    for(unsigned iD(0); iD != field.getNDim(); ++iD){
      double dphi(field.getDerivative(_coord, iD, _trial));
      sumDphi2 += dphi * dphi;
    }
    return 0.5 * sumDphi2 - 0.5 * mu2_ * phi2 - lambda_ * phi2 * phi2;
  }
  
  void
  QuarticPotential::setParameter(unsigned _idx, double _val)
  {
    switch(_idx){
    case 0:
      mu2_ = _val;
      break;
    case 1:
      lambda_ = _val;
      break;
    }
  }

  DEFINE_LATTICE_ACTION(QuarticPotential);
    
}
