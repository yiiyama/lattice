#include "Main.h"

#include "TRandom2.h"
#include "TFile.h"
#include "TTree.h"

#include <string>
#include <vector>
#include <cmath>
#include <iostream>

namespace lattice {

  class Output {
  public:
    Output(std::string const& _fileName, ActionBase const* _L) :
      file_(TFile::Open(_fileName.c_str(), "recreate")),
      configurations_(new TTree("config", "Lattice configuration")),
      L_(_L),
      Lvalue_(0.),
      fvalues_()
    {
      configurations_->Branch("L", &Lvalue_, "L/D");
      for(Coordinate coord(L_->getObj()->getCoord(0)); coord.isValid(); coord.next())
        fvalues_.push_back(0.);

      unsigned iF(0);
      for(Coordinate coord(L_->getObj()->getCoord(0)); coord.isValid(); coord.next()){
        std::string name(coord.getName());
        configurations_->Branch(name.c_str(), &(fvalues_[iF++]), (name + "/D").c_str());
      }
    }
    ~Output()
    {
      delete file_;
    }

    void fill()
    {
      Lvalue_ = L_->eval();
      PhysicsBase const* obj(L_->getObj());
      unsigned iX(0);
      for(Coordinate coord(obj->getCoord(0)); coord.isValid(); coord.next())
        fvalues_[iX++] = obj->getVal(coord);

      configurations_->Fill();
    }
    void finalize()
    {
      file_->cd();
      file_->Write();
      delete file_;
      file_ = 0;
      configurations_ = 0;
    }

  private:
    TFile* file_;
    TTree* configurations_;

    ActionBase const* L_;
    double Lvalue_;
    std::vector<double> fvalues_;
  };

  LatticeSimulation::LatticeSimulation(ActionBase* _L) :
    L_(_L),
    nSweeps_(10000),
    nTherm_(1000),
    fillInterval_(100),
    df_(0.1),
    outputName_("lattice.root"),
    seed_(0)
  {
  }

  LatticeSimulation::~LatticeSimulation()
  {}

  void
  LatticeSimulation::run()
  {
    TRandom2 rand(seed_);

    Output output(outputName_, L_);

    PhysicsBase* obj(L_->getObj());

    std::cout << "Initializing the lattice" << std::endl;
   
    obj->randomize(rand, df_);

    output.fill();

    double lval(L_->eval());

    unsigned nTrial(0);
    unsigned nAccept(0);

    std::cout << "Thermalizing the system" << std::endl;
    bool thermalized(false);

    for(unsigned iSweep(0); iSweep != nSweeps_; ++iSweep){
      if(iSweep % 1000 == 0) (std::cout << "\r" << iSweep).flush();
      
      for(Coordinate coord(obj->getCoord(0)); coord.isValid(); coord.next()){
        if(obj->isFixed(coord)) continue;
        
        if(thermalized) ++nTrial;

        obj->trial(coord, rand.Uniform(-df_, df_));
        double trial(L_->eval());

        if(std::exp(lval - trial) > rand.Uniform(0., 1.)){
          if(thermalized) ++nAccept;
          obj->update();
          lval = trial;
        }
        else
          obj->clearTrial();
      }

      if(iSweep < nTherm_) continue;
      if(!thermalized){
        std::cout << std::endl << "Start data taking" << std::endl;
        thermalized = true;
      }

      if(iSweep % fillInterval_ == 0) output.fill();
    }
    std::cout << std::endl;

    std::cout << "acceptance = " << (double(nAccept) / nTrial) << std::endl;

    output.finalize();
  }

}
