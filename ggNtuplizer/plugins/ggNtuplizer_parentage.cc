// #include <memory>
// #include <string>
// #include <iostream>
// #include <sstream>

// #include "FWCore/Framework/interface/Frameworkfwd.h"
// #include "FWCore/Framework/interface/EDAnalyzer.h"
// #include "FWCore/Framework/interface/ESHandle.h"
// #include "FWCore/Framework/interface/Event.h"
// #include "FWCore/Framework/interface/EventSetup.h"
// #include "FWCore/Framework/interface/MakerMacros.h"
// #include "FWCore/ParameterSet/interface/ParameterSet.h"
// #include "FWCore/Utilities/interface/InputTag.h"
// #include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
// #include "DataFormats/Candidate/interface/Candidate.h"
// #include "DataFormats/Candidate/interface/CandidateFwd.h"
// #include "DataFormats/HepMCCandidate/interface/GenParticle.h"
// #include "DataFormats/Common/interface/Ref.h"


// std::vector<const reco::Candidate *> _allGenParticles;
// edm::Handle<reco::CandidateView> _GenParticlesHandle;
// std::vector<const reco::Candidate> *_parents;

// void ggNtuplizer::collectGenParticles(){
// 	allGenParticles.clear();
// 	_GenParticlesHandle.clear();
// 	iEvent.getByToken(genParticlesCollection_, _GenParticlesHandle);
// 	for(CandidateView::const_iterator p = _GenParticlesHandle->begin(); p != _GenParticlesHandle->end(); p++){
// 		cands.push_back(&*p);
// 	}
// };

// void ggNtuplizer::getMothers(reco::Candidate *_particle, Int_t _pdgID){
// 	if( _particle->numberOfMothers() == 0 ) return;
// 	if ( daughterId != 0 && !_realParent.isNonnull() &&	p->pdgId() != daughterId ) {
// 		_parents.push_back();
// 	}

// };
