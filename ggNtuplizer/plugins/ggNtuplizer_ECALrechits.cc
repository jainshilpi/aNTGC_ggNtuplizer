#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"



std::vector<Float_t> ecalSC_LICTD_;
std::vector<Float_t> ecalSC_SwissCross_;
std::vector<UChar_t> ecalSC_nDiweird_;
std::vector<UChar_t> ecalSC_nWeird_;
std::vector<UChar_t> ecalSC_nSaturated_;
std::vector<UChar_t> ecalSC_nTime_;
std::vector<UChar_t> ecalSC_nXtals_;
std::vector<UChar_t> ecalSC_SeedXtalBits_;



Float_t ggNtuplizer::ECALrecHitE( const DetId & id, const EcalRecHitCollection & recHits, int di, int dj){
	DetId nid;
	if(di == 0 && dj == 0) nid = id;
	else if( id.subdetId() == EcalBarrel) nid = EBDetId::offsetBy( id, di, dj );
	else if( id.subdetId() == EcalEndcap) nid = EEDetId::offsetBy( id, di, dj );
	return ((recHits.find(nid) != recHits.end()) ? recHits.find(nid)->energy() : -999.);
};



Float_t ggNtuplizer::swissCross(const DetId& id, const EcalRecHitCollection & recHits){
	if ( id.subdetId() == EcalBarrel ) {
		EBDetId ebId( id );
	    // avoid recHits at |iEta|=85 where one side of the neighbours is missing
		if (std::abs(ebId.ieta())==85) return -100.;
		Float_t e1 = ECALrecHitE(id, recHits);
		Float_t s4 = 0.;
		if (!(e1 > 0.)) return -900.;
		s4 += ECALrecHitE( id, recHits,  1,  0 );
		s4 += ECALrecHitE( id, recHits, -1,  0 );
		s4 += ECALrecHitE( id, recHits,  0,  1 );
		s4 += ECALrecHitE( id, recHits,  0, -1 );
		return (1 - s4 / e1);
	} else if ( id.subdetId() == EcalEndcap ) {
		EEDetId eeId( id );
		Float_t e1 = ECALrecHitE(id, recHits);
		Float_t s4 = 0.;
		if (!(e1 > 0.)) return -920.;
		s4 += ECALrecHitE( id, recHits,  1,  0 );
		s4 += ECALrecHitE( id, recHits, -1,  0 );
		s4 += ECALrecHitE( id, recHits,  0,  1 );
		s4 += ECALrecHitE( id, recHits,  0, -1 );
		return (1 - s4 / e1);
	}
	return -9999.;
};



void ggNtuplizer::branchesECALSC(TTree* tree) {
	tree->Branch("ecalSC_LICTD",                    &ecalSC_LICTD_);
	tree->Branch("ecalSC_SwissCross",             	&ecalSC_SwissCross_);
	tree->Branch("ecalSC_nDiweird",                 &ecalSC_nDiweird_);
	tree->Branch("ecalSC_nWeird",					&ecalSC_nWeird_);
	tree->Branch("ecalSC_nSaturated",				&ecalSC_nSaturated_);
	tree->Branch("ecalSC_nTime",					&ecalSC_nTime_);
	tree->Branch("ecalSC_nXtals",					&ecalSC_nXtals_);
	tree->Branch("ecalSC_SeedXtalBits",				&ecalSC_SeedXtalBits_);
};



Float_t ggNtuplizer::getLICTD(const reco::SuperCluster & sc, noZS::EcalClusterLazyTools & ltNoZS){

	Float_t _seedXtalTime 		= ltNoZS.SuperClusterSeedTime(sc);
	Float_t _LICTD 				= -999;

	if(sc.clustersSize() < 1) return -99.;

	DetId id = sc.seed()->hitsAndFractions()[0].first;
	const EcalRecHitCollection *recHits = nullptr;
	if (id.subdetId() == EcalBarrel) recHits = ltNoZS.getEcalEBRecHitCollection();
	else if ( id.subdetId() == EcalEndcap)	recHits = ltNoZS.getEcalEERecHitCollection();

	for(reco::CaloCluster_iterator cluster = sc.clustersBegin(); cluster != sc.clustersEnd(); cluster++){
		for(const std::pair<DetId, Float_t> & _xtal : (*cluster)->hitsAndFractions()){
			EcalRecHitCollection::const_iterator _xtalHit = recHits->find (_xtal.first);
			if(_xtalHit == recHits->end()) continue;
			Float_t _xtalTD = std::abs(_xtalHit->time() - _seedXtalTime);
			if(_xtalTD > _LICTD) _LICTD = _xtalTD;
		}
	};
	return _LICTD;
};



void ggNtuplizer::fillECALSC(const edm::Event& e, const edm::EventSetup& es){

	noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

};
