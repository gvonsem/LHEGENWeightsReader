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
//#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenLumiInfoHeader.h"

//
// class declaration
//

//class GENWeightsReader : public edm::one::EDAnalyzer<edm::one::WatchLuminosityBlocks> {
class GENWeightsReader : public edm::EDAnalyzer { 
   public:
      explicit GENWeightsReader(const edm::ParameterSet&);
      ~GENWeightsReader();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      void beginLuminosityBlock(const edm::LuminosityBlock&, const edm::EventSetup&) override;
      void analyze(const edm::Event&, const edm::EventSetup&) override;
      void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //void endRun(edm::Run const&, edm::EventSetup const&);

      edm::InputTag genProduct_;
      edm::EDGetTokenT<GenLumiInfoHeader> genToken_;
};


GENWeightsReader::GENWeightsReader(const edm::ParameterSet& iConfig):
genProduct_( iConfig.getParameter<edm::InputTag>("genProduct") )
{
   genToken_ = consumes <GenLumiInfoHeader,edm::InLumi> (edm::InputTag(genProduct_));
   return;
}


GENWeightsReader::~GENWeightsReader()
{
}


void
GENWeightsReader::beginLuminosityBlock(const edm::LuminosityBlock& iRun, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<GenLumiInfoHeader> genLumiHeader;
   iRun.getByToken(genToken_, genLumiHeader);
   //iRun.getByLabel("generator", genLumiHeader);

   for(unsigned int i=0; i<genLumiHeader->weightNames().size(); i++){
     std::cout << "Weight " << i << " " << genLumiHeader->weightNames()[i] << std::endl;
   }

}


void
GENWeightsReader::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
}


void
GENWeightsReader::endLuminosityBlock(const edm::LuminosityBlock& iRun, const edm::EventSetup& iSetup)
{
}


// void
// GENWeightsReader::endRun(edm::Run const& iRun, edm::EventSetup const&)
// {
// }


void
GENWeightsReader::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}


//define this as a plug-in
DEFINE_FWK_MODULE(GENWeightsReader);
