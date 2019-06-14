#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "limits"


UShort_t necalSC_;
std::vector<UShort_t> ecalSCindex_;
std::vector<Float_t> ecalSCeta_;
std::vector<Float_t> ecalSCphi_;
std::vector<Float_t> ecalSC_LICTD_;
std::vector<UChar_t> ecalSC_nL1Spike_;
std::vector<UChar_t> ecalSC_nDiweird_;
std::vector<UChar_t> ecalSC_nWeird_;
std::vector<UChar_t> ecalSC_nSaturated_;
std::vector<UChar_t> ecalSC_nOutOfTime_;
std::vector<UChar_t> ecalSC_nXtals_;
std::vector<Float_t> ecalSC_maxEnXtalTime_;
std::vector<Float_t> ecalSC_maxEnXtalSwissCross_;
std::vector<UChar_t> ecalSC_maxEnXtalBits_;



Float_t ggNtuplizer::ECALrecHitE( const DetId & id, const EcalRecHitCollection *recHits, int di, int dj){
	DetId nid;
	if(di == 0 && dj == 0) nid = id;
	else if( id.subdetId() == EcalBarrel) nid = EBDetId::offsetBy( id, di, dj );
	else if( id.subdetId() == EcalEndcap) nid = EEDetId::offsetBy( id, di, dj );
	return ((recHits->find(nid) != recHits->end()) ? recHits->find(nid)->energy() : 0.);
};



Float_t ggNtuplizer::swissCross(const DetId & id, noZS::EcalClusterLazyTools & ltNoZS){
	const EcalRecHitCollection * recHits = nullptr;
	if ( id.subdetId() == EcalBarrel ) {
		recHits = ltNoZS.getEcalEBRecHitCollection();
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
		recHits = ltNoZS.getEcalEERecHitCollection();
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
	tree->Branch("necalSC",                    		&necalSC_);
	tree->Branch("ecalSCindex",                    	&ecalSCindex_);
	tree->Branch("ecalSCeta",                    	&ecalSCeta_);
	tree->Branch("ecalSCphi",                    	&ecalSCphi_);
	tree->Branch("ecalSC_LICTD",                    &ecalSC_LICTD_);
	tree->Branch("ecalSC_nL1Spike",                 &ecalSC_nL1Spike_);
	tree->Branch("ecalSC_nDiweird",                 &ecalSC_nDiweird_);
	tree->Branch("ecalSC_nWeird",					&ecalSC_nWeird_);
	tree->Branch("ecalSC_nSaturated",				&ecalSC_nSaturated_);
	tree->Branch("ecalSC_nOutOfTime",				&ecalSC_nOutOfTime_);
	tree->Branch("ecalSC_nXtals",					&ecalSC_nXtals_);
	tree->Branch("ecalSC_maxEnXtalTime",			&ecalSC_maxEnXtalTime_);
	tree->Branch("ecalSC_maxEnXtalSwissCross",		&ecalSC_maxEnXtalSwissCross_);
	tree->Branch("ecalSC_maxEnXtalBits",			&ecalSC_maxEnXtalBits_);
};



Float_t ggNtuplizer::getLICTD(const reco::SuperCluster *sc, noZS::EcalClusterLazyTools & ltNoZS, Float_t &_maxEnXtalTime, UChar_t & _nL1Spike, UChar_t & _nDiweird, UChar_t & _nWeird, UChar_t & _nSaturated, UChar_t & _nOutOfTime, UChar_t & _nXtals, UChar_t & _maxEnXtalBits, Float_t & _maxEnXtalSwissCross){

	_maxEnXtalTime = -999.;
	_nL1Spike = 0;
	_nDiweird = 0;
	_nWeird = 0;
	_nSaturated = 0;
	_nOutOfTime = 0;
	_nXtals = 0;
	_maxEnXtalBits= 0;
	_maxEnXtalSwissCross = -999.;

	if(sc->clustersSize()<1) return -999999.;
	if(!sc->clusters().isAvailable()) return -999999.;

	std::cout<<"\t\tscSize = "<<sc->clustersSize()<<std::endl;

	DetId seedDetID = sc->seed()->seed();
	Bool_t isEB = (seedDetID.subdetId() == EcalBarrel);
	if(!isEB && !(seedDetID.subdetId() == EcalEndcap)) return -999.;

	const EcalRecHitCollection *recHitsEB = ltNoZS.getEcalEBRecHitCollection();
	const EcalRecHitCollection *recHitsEE = ltNoZS.getEcalEERecHitCollection();

	std::vector<uint32_t> _detIDs_nL1Spike;
	std::vector<uint32_t> _detIDs_nDiweird;
	std::vector<uint32_t> _detIDs_nWeird;
	std::vector<uint32_t> _detIDs_nSaturated;
	std::vector<uint32_t> _detIDs_nOutOfTime;
	std::vector<uint32_t> _detIDs_nXtals;

	const EcalRecHit *maxEnergyXtalRecHit_ 	= nullptr;
	Float_t maxEnergyXtal_ 					= std::numeric_limits<Float_t>::min();
	Float_t maxTime_						= std::numeric_limits<Float_t>::min();
	Float_t minTime_						= std::numeric_limits<Float_t>::max();

	for(reco::CaloCluster_iterator cluster = sc->clustersBegin(); cluster != sc->clustersEnd(); cluster++){
		if((*cluster)->size()<1) continue;

		for(const std::pair<DetId, Float_t> & _xtal : (*cluster)->hitsAndFractions()){

			// Find rechit
			const EcalRecHit * _xtalHit = nullptr;
			if(isEB){
				if(recHitsEB->find(_xtal.first) != recHitsEB->end()) _xtalHit = &(*(recHitsEB->find (_xtal.first)));
				else if(recHitsEE->find(_xtal.first) != recHitsEE->end()) _xtalHit = &(*(recHitsEE->find (_xtal.first)));
			} else{
				if(recHitsEE->find(_xtal.first) != recHitsEE->end()) _xtalHit = &(*(recHitsEE->find (_xtal.first)));
				else if(recHitsEB->find(_xtal.first) != recHitsEB->end()) _xtalHit = &(*(recHitsEB->find (_xtal.first)));
			}
			if(!_xtalHit) continue;

			// Get time range and max energy xtal
			if(_xtalHit->time() > maxTime_) maxTime_ = _xtalHit->time();
			if(_xtalHit->time() < minTime_) minTime_ = _xtalHit->time();
			if(_xtalHit->energy() > maxEnergyXtal_){
				maxEnergyXtal_ = _xtalHit->energy();
				maxEnergyXtalRecHit_ = &(*(recHitsEB->find (_xtal.first)));
			}

			uint32_t _xtalDetID = _xtal.first.rawId();
			if(_xtalHit->checkFlag( EcalRecHit::kL1SpikeFlag ) && (std::find(_detIDs_nL1Spike.begin(), _detIDs_nL1Spike.end(), _xtalDetID) == _detIDs_nL1Spike.end())){
				_detIDs_nL1Spike.push_back(_xtalDetID);
				_nL1Spike++;
			}
			if(_xtalHit->checkFlag( EcalRecHit::kDiWeird ) && (std::find(_detIDs_nDiweird.begin(), _detIDs_nDiweird.end(), _xtalDetID) == _detIDs_nDiweird.end())){
				_detIDs_nDiweird.push_back(_xtalDetID);
				_nDiweird++;
			}
			if(_xtalHit->checkFlag( EcalRecHit::kWeird ) && (std::find(_detIDs_nWeird.begin(), _detIDs_nWeird.end(), _xtalDetID) == _detIDs_nWeird.end())){
				_detIDs_nWeird.push_back(_xtalDetID);
				_nWeird++;
			}
			if(_xtalHit->checkFlag( EcalRecHit::kSaturated ) && (std::find(_detIDs_nSaturated.begin(), _detIDs_nSaturated.end(), _xtalDetID) == _detIDs_nSaturated.end())){
				_detIDs_nSaturated.push_back(_xtalDetID);
				_nSaturated++;
			}
			if(_xtalHit->checkFlag( EcalRecHit::kOutOfTime ) && (std::find(_detIDs_nOutOfTime.begin(), _detIDs_nOutOfTime.end(), _xtalDetID) == _detIDs_nOutOfTime.end())){
				_detIDs_nOutOfTime.push_back(_xtalDetID);
				_nOutOfTime++;
			}
			if(std::find(_detIDs_nOutOfTime.begin(), _detIDs_nOutOfTime.end(), _xtalDetID) == _detIDs_nOutOfTime.end()){
				_detIDs_nXtals.push_back(_xtalDetID);
				_nXtals++;
			}
		}
	};

	if(!maxEnergyXtalRecHit_) return -9999.;
	_maxEnXtalTime 		= maxEnergyXtalRecHit_->time();
	_maxEnXtalBits = 0;
	if(maxEnergyXtalRecHit_->checkFlag( EcalRecHit::kDiWeird )) setbit(_maxEnXtalBits, 0);
	if(maxEnergyXtalRecHit_->checkFlag( EcalRecHit::kWeird )) setbit(_maxEnXtalBits, 1);
	if(maxEnergyXtalRecHit_->checkFlag( EcalRecHit::kSaturated )) setbit(_maxEnXtalBits, 2);
	if(maxEnergyXtalRecHit_->checkFlag( EcalRecHit::kOutOfTime )) setbit(_maxEnXtalBits, 3);

	_maxEnXtalSwissCross = swissCross(maxEnergyXtalRecHit_->detid(), ltNoZS);
	if(maxEnergyXtalRecHit_->detid().rawId() != seedDetID.rawId()) setbit(_maxEnXtalBits, 4);

	Float_t LICTD_ = std::max(std::abs(maxTime_ - _maxEnXtalTime), std::abs(_maxEnXtalTime - minTime_));

	return LICTD_;
};



void ggNtuplizer::fillECALSC(const edm::Event& e, const edm::EventSetup& es){
	cout<<e.id().event()<<endl;
	necalSC_ = 0;
	ecalSCindex_.clear();
	ecalSCeta_.clear();
	ecalSCphi_.clear();
	ecalSC_LICTD_.clear();
	ecalSC_nL1Spike_.clear();
	ecalSC_nDiweird_.clear();
	ecalSC_nWeird_.clear();
	ecalSC_nSaturated_.clear();
	ecalSC_nOutOfTime_.clear();
	ecalSC_nXtals_.clear();
	ecalSC_maxEnXtalTime_.clear();
	ecalSC_maxEnXtalSwissCross_.clear();
	ecalSC_maxEnXtalBits_.clear();


	edm::Handle<std::vector<reco::SuperCluster>> ecalSChandle;
	e.getByToken(ecalSCcollection_, ecalSChandle);

	noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

	if(ecalSChandle.isValid()){

		UShort_t _scIndex_ = 0;
		for(std::vector<reco::SuperCluster>::const_iterator iSC = ecalSChandle->begin(); iSC != ecalSChandle->end(); iSC++){
			_scIndex_++;
			ecalSCindex_.push_back(_scIndex_-1);
			if(iSC->energy() < 15.) continue;
			necalSC_++;
			Float_t maxEnXtalTime = -999.;
			UChar_t tmpnL1Spike	= 0;
			UChar_t tmpnDiweird = 0;
			UChar_t tmpnWeird = 0;
			UChar_t tmpnSaturated = 0;
			UChar_t tmpnOutOfTime = 0;
			UChar_t tmpnXtals = 0;
			Float_t tmpmaxEnXtalSwissCross = -999;
			UChar_t tmpmaxEnXtalBits = 0;
			Float_t tmpscEta = iSC->eta();
			Float_t tmpscPhi = iSC->phi();
			Float_t tmpecalSC_LICTD =  getLICTD(&(*iSC), lazyToolnoZS, maxEnXtalTime, tmpnL1Spike, tmpnDiweird, tmpnWeird, tmpnSaturated, tmpnOutOfTime, tmpnXtals, tmpmaxEnXtalBits, tmpmaxEnXtalSwissCross);

			ecalSCeta_.push_back(tmpscEta);
			ecalSCphi_.push_back(tmpscPhi);
			ecalSC_LICTD_.push_back(tmpecalSC_LICTD);
			ecalSC_nL1Spike_.push_back(tmpnL1Spike);
			ecalSC_nDiweird_.push_back(tmpnDiweird);
			ecalSC_nWeird_.push_back(tmpnWeird);
			ecalSC_nSaturated_.push_back(tmpnSaturated);
			ecalSC_nOutOfTime_.push_back(tmpnOutOfTime);
			ecalSC_nXtals_.push_back(tmpnXtals);
			ecalSC_maxEnXtalTime_.push_back(maxEnXtalTime);
			ecalSC_maxEnXtalSwissCross_.push_back(tmpmaxEnXtalSwissCross);
			ecalSC_maxEnXtalBits_.push_back(tmpmaxEnXtalBits);
		}
	}
};
