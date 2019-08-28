//
// Original Author:  Lorenzo Viliani
//         Created:  Fri, 30 Nov 2018 09:20:09 GMT
//
// Adapted for GEN weights instead of LHE weights: Gerrit Van Onsem

// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

//
// class declaration
//

class GENWeightsDumper : public edm::EDAnalyzer {
   public:
      explicit GENWeightsDumper(const edm::ParameterSet&);
      ~GENWeightsDumper();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      void analyze(const edm::Event&, const edm::EventSetup&) override;
      void endRun(edm::Run const&, edm::EventSetup const&) override;

      edm::InputTag genProduct_;
      edm::EDGetTokenT<GenEventInfoProduct> genToken_;
};


GENWeightsDumper::GENWeightsDumper(const edm::ParameterSet& iConfig):
genProduct_( iConfig.getParameter<edm::InputTag>("genProduct") )
{
   genToken_ = consumes <GenEventInfoProduct> (edm::InputTag(genProduct_));

   return;
}


GENWeightsDumper::~GENWeightsDumper()
{
}


void
GENWeightsDumper::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   
   edm::Handle<GenEventInfoProduct> event;
  
   iEvent.getByToken(genToken_,event);

   for (unsigned int i=0; i<event->weights().size(); i++) {
     std::cout << "Weight " << i << " " <<  event->weights().at(i) << std::endl;
   }

}


void
GENWeightsDumper::endRun(edm::Run const& iRun, edm::EventSetup const&)
{
}

void
GENWeightsDumper::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}


//define this as a plug-in
DEFINE_FWK_MODULE(GENWeightsDumper);
