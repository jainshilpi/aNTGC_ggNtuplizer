#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"
#include "ggAnalysis/ggNtuplizer/interface/GenParticleParentage.h"
using namespace std;

// (local) variables associated with tree branches
Int_t            nGenJets_;
vector<float>  genJetEn_;
vector<float>  genJetPt_;
vector<float>  genJetEta_;
vector<float>  genJetPhi_;
vector<float>  genJetEMenergy_;
vector<float>  genJetHADenergy_;
vector<float>  genJetINVenergy_;


void ggNtuplizer::branchesGenJetPart(TTree* tree) {

  // tree->Branch("nGenJets",     &nGenJets_);
  tree->Branch("genJetEn",       &genJetEn_);
  tree->Branch("genJetPt",       &genJetPt_);
  tree->Branch("genJetEta",      &genJetEta_);
  tree->Branch("genJetPhi",      &genJetPhi_);
  tree->Branch("genJetEMenergy",      &genJetEMenergy_);
  tree->Branch("genJetHADenergy",      &genJetHADenergy_); 
}

void ggNtuplizer::fillGenJetInfo(const edm::Event& e) {

  nGenJets_ = -99;
  genJetEn_.clear();
  genJetPt_.clear();
  genJetEta_.clear();
  genJetPhi_.clear();
  genJetEMenergy_.clear();
  genJetHADenergy_.clear();
  genJetINVenergy_.clear();
  
  if(doGenJets_){

    edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
    if(doGenParticles_)e.getByToken(genParticlesCollection_, genParticlesHandle);

    // Get GenJets
    edm::Handle<std::vector<reco::GenJet>> ak4PFJetsCHSgenjets;
    e.getByToken(ak4PFJetsCHSGenJetLabel_,ak4PFJetsCHSgenjets);
    if(!ak4PFJetsCHSgenjets.isValid()) {
      edm::LogWarning("ggNtuplizer") << "Could not find GenJet vector named ";
      return;
    }
    
    nGenJets_= ak4PFJetsCHSgenjets->size();

    for (vector<reco::GenJet>::const_iterator ip = ak4PFJetsCHSgenjets->begin(); ip != ak4PFJetsCHSgenjets->end(); ++ip) {
      genJetEn_.push_back(ip->energy());
      genJetPt_.push_back(ip->pt());
      genJetEta_.push_back(ip->eta());
      genJetPhi_.push_back(ip->phi());
      genJetEMenergy_.push_back(ip->emEnergy () );
      genJetHADenergy_.push_back(ip->hadEnergy ());
      genJetINVenergy_.push_back(ip->invisibleEnergy ());

    }

  }
}


