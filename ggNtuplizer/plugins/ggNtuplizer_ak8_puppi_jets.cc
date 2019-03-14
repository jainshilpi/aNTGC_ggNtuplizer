#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
// #include "FWCore/Utilities/interface/RandomNumberGenerator.h"
// #include "CLHEP/Random/RandomEngine.h"
// #include "CLHEP/Random/RandGauss.h"

using namespace std;
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

Int_t         nAK8PUPPIJet_;
vector<float> AK8PUPPIJet_Pt_;
vector<float> AK8PUPPIJet_En_;
vector<float> AK8PUPPIJet_RawPt_;
vector<float> AK8PUPPIJet_RawEn_;
vector<float> AK8PUPPIJet_Eta_;
vector<float> AK8PUPPIJet_Phi_;
vector<float> AK8PUPPIJet_Mass_;
vector<float> AK8PUPPIJet_tau1_;
vector<float> AK8PUPPIJet_tau2_;
vector<float> AK8PUPPIJet_tau3_;
vector<float> AK8PUPPIJet_tau4_;
vector<float> AK8PUPPIJet_CHF_;
vector<float> AK8PUPPIJet_NHF_;
vector<float> AK8PUPPIJet_CEF_;
vector<float> AK8PUPPIJet_NEF_;
vector<int>   AK8PUPPIJet_NCH_;
vector<int>   AK8PUPPIJet_NNP_;
vector<float> AK8PUPPIJet_MUF_;
vector<int>   AK8PUPPIJet_nconstituents_;
vector<Char_t> AK8PUPPIJet_PFid_;
vector<float> AK8PUPPIJet_PUPPISoftDropMass_;
vector<float> AK8PUPPIJet_CHSPrunedMass_;
vector<float> AK8PUPPIJet_CHSSoftDropMass_;
vector<float> AK8PUPPIJet_pfBoostedDSVBTag_;
vector<float> AK8PUPPIJet_DSVnewV4_;
vector<float> AK8PUPPIJet_CSV_;
vector<float> AK8PUPPIJet_JECUnc_;
vector<float> AK8PUPPIJet_L2L3corr_;
vector<float> AK8PUPPIJet_JER_sf_;
vector<float> AK8PUPPIJet_JER_sf_up_;
vector<float> AK8PUPPIJet_JER_sf_down_;
vector<Float_t> AK8PUPPIJet_JER_ptRes_;
vector<Float_t> AK8PUPPIJet_JER_phiRes_;
vector<float>  AK8PUPPIJet_nb1ecf2_;
vector<float>  AK8PUPPIJet_nb1ecf3_;
vector<float>  AK8PUPPIJet_nb2ecf2_;
vector<float>  AK8PUPPIJet_nb2ecf3_;
vector<int>   AK8PUPPIJet_PartonFlavour_;
vector<int>   AK8PUPPIJet_HadronFlavour_;
vector<int>   AK8PUPPIJet_GenJetIndex_;
vector<int>   AK8PUPPIJet_GenPartonID_;
vector<float> AK8PUPPIJet_GenPartonIndex_;
vector<float> AK8PUPPIJet_GenJetEn_;
vector<float> AK8PUPPIJet_GenJetPt_;
vector<float> AK8PUPPIJet_GenJetEta_;
vector<float> AK8PUPPIJet_GenJetPhi_;
vector<int>   AK8PUPPIJet_GenPartonID_;
vector<int>             nAK8PUPPIJet_SDSJ_ ;
vector< vector<float> > AK8PUPPIJet_SDSJPt_ ;
vector< vector<float> > AK8PUPPIJet_SDSJEta_ ;
vector< vector<float> > AK8PUPPIJet_SDSJMass_ ;
vector< vector<float> > AK8PUPPIJet_SDSJPhi_ ;
vector< vector<float> > AK8PUPPIJet_SDSJE_ ;
vector< vector<int > >  AK8PUPPIJet_SDSJCharge_ ;
vector< vector<int > >  AK8PUPPIJet_SDSJFlavour_;
vector< vector<float> > AK8PUPPIJet_SDSJCSV_ ;
vector< vector<float> > AK8PUPPIJet_SDSJnb1ecf2_;
vector< vector<float> > AK8PUPPIJet_SDSJnb1ecf3_;
vector< vector<float> > AK8PUPPIJet_SDSJnb2ecf2_;
vector< vector<float> > AK8PUPPIJet_SDSJnb2ecf3_;


void ggNtuplizer::branchesAK8PUPPIJets(TTree* tree) {
	tree->Branch("nAK8PUPPIJet",                  &nAK8PUPPIJet__);
	tree->Branch("AK8PUPPIJet_Pt",                 &AK8PUPPIJet_Pt_);
	tree->Branch("AK8PUPPIJet_En",                 &AK8PUPPIJet_En_);
	tree->Branch("AK8PUPPIJet_RawPt",              &AK8PUPPIJet_RawPt_);
	tree->Branch("AK8PUPPIJet_RawEn",              &AK8PUPPIJet_RawEn_);
	tree->Branch("AK8PUPPIJet_Eta",                &AK8PUPPIJet_Eta_);
	tree->Branch("AK8PUPPIJet_Phi",                &AK8PUPPIJet_Phi_);
	tree->Branch("AK8PUPPIJet_Mass",               &AK8PUPPIJet_Mass_);
	tree->Branch("AK8PUPPIJet_tau1",              &AK8PUPPIJet_tau1_);
	tree->Branch("AK8PUPPIJet_tau2",              &AK8PUPPIJet_tau2_);
	tree->Branch("AK8PUPPIJet_tau3",              &AK8PUPPIJet_tau3_);
	tree->Branch("AK8PUPPIJet_tau4",              &AK8PUPPIJet_tau3_);
	tree->Branch("AK8PUPPIJet_CHF",                &AK8PUPPIJet_CHF_);
	tree->Branch("AK8PUPPIJet_NHF",                &AK8PUPPIJet_NHF_);
	tree->Branch("AK8PUPPIJet_CEF",                &AK8PUPPIJet_CEF_);
	tree->Branch("AK8PUPPIJet_NEF",                &AK8PUPPIJet_NEF_);
	tree->Branch("AK8PUPPIJet_NCH",                &AK8PUPPIJet_NCH_);
	tree->Branch("AK8PUPPIJet_NNP",                &AK8PUPPIJet_NNP_);
	tree->Branch("AK8PUPPIJet_MUF",                &AK8PUPPIJet_MUF_);
	tree->Branch("AK8PUPPIJet_nconstituents",      &AK8PUPPIJet_nconstituents_);
	tree->Branch("AK8PUPPIJet_PFLooseId",          &AK8PUPPIJet_PFid_);
	tree->Branch("AK8PUPPIJet_PUPPISoftDropMass",       &AK8PUPPIJet_PUPPISoftDropMass_);
	tree->Branch("AK8PUPPIJet_CHSPrunedMass",         &AK8PUPPIJet_CHSPrunedMass_);
	tree->Branch("AK8PUPPIJet_CHSSoftDropMass",         &AK8PUPPIJet_CHSSoftDropMass_);
	tree->Branch("AK8PUPPIJet_pfBoostedDSVBTag",   &AK8PUPPIJet_pfBoostedDSVBTag_);
	tree->Branch("AK8PUPPIJet_DSVnewV4",           &AK8PUPPIJet_DSVnewV4_);
	tree->Branch("AK8PUPPIJet_CSV",                &AK8PUPPIJet_CSV_);
	tree->Branch("AK8PUPPIJet_JECUnc",             &AK8PUPPIJet_JECUnc_);
	tree->Branch("AK8PUPPIJet_L2L3corr",           &AK8PUPPIJet_L2L3corr_);
	tree->Branch("AK8PUPPIJet_JER_sf",           &AK8PUPPIJet_JER_sf_);
	tree->Branch("AK8PUPPIJet_JER_sf_up",           &AK8PUPPIJet_JER_sf_up_);
	tree->Branch("AK8PUPPIJet_JER_sf_down",           &AK8PUPPIJet_JER_sf_down);
	tree->Branch("AK8PUPPIJet_JER_ptRes",           &AK8PUPPIJet_JER_ptRes_);
	tree->Branch("AK8PUPPIJet_JER_phiRes",           &AK8PUPPIJet_JER_phiRes_);
	tree->Branch("AK8PUPPIJet_nb1ecf2",           &AK8PUPPIJet_nb1ecf2_);
	tree->Branch("AK8PUPPIJet_nb1ecf3",           &AK8PUPPIJet_nb1ecf3_);
	tree->Branch("AK8PUPPIJet_nb2ecf2",           &AK8PUPPIJet_nb2ecf2_);
	tree->Branch("AK8PUPPIJet_nb2ecf3",           &AK8PUPPIJet_nb2ecf3);
	if (doGenParticles_){
		tree->Branch("AK8PUPPIJet_PartonID",       &AK8PUPPIJ87et_PartonFlavour_);
		tree->Branch("AK8PUPPIJet_HadronFlavour",        &AK8PUPPIJet_HadronFlavour_);
		tree->Branch("AK8PUPPIJet_GenJetIndex",    &AK8PUPPIJet_GenJetIndex_);
		tree->Branch("AK8PUPPIJet_GenPartonID",    &AK8PUPPIJet_GenPartonID_);
		tree->Branch("AK8PUPPIJet_GenPartonIndex",    &AK8PUPPIJet_GenPartonIndex_);
		tree->Branch("AK8PUPPIJet_GenJetEn",       &AK8PUPPIJet_GenJetEn_);
		tree->Branch("AK8PUPPIJet_GenJetPt",       &AK8PUPPIJet_GenJetPt_);
		tree->Branch("AK8PUPPIJet_GenJetEta",      &AK8PUPPIJet_GenJetEta_);
		tree->Branch("AK8PUPPIJet_GenJetPhi",      &AK8PUPPIJet_GenJetPhi_);
	}
	tree->Branch("nAK8PUPPIJet_SDSJ",            &nAK8PUPPIJet_SDSJ_);
	tree->Branch("nAK8PUPPIJet_SDSJPt",           &nAK8PUPPIJet_SDSJPt_);
	tree->Branch("nAK8PUPPIJet_SDSJEta",          &nAK8PUPPIJet_SDSJEta_);
	tree->Branch("nAK8PUPPIJet_SDSJMass",         &nAK8PUPPIJet_SDSJMass_);
	tree->Branch("nAK8PUPPIJet_SDSJPhi",          &nAK8PUPPIJet_SDSJPhi_);
	tree->Branch("nAK8PUPPIJet_SDSJE",            &nAK8PUPPIJet_SDSJE_);
	tree->Branch("nAK8PUPPIJet_SDSJCharge",       &nAK8PUPPIJet_SDSJCharge_);
	tree->Branch("nAK8PUPPIJet_SDSJFlavour",      &nAK8PUPPIJet_SDSJFlavour_);
	tree->Branch("nAK8PUPPIJet_SDSJCSV",          &nAK8PUPPIJet_SDSJCSV_);
	tree->Branch("AK8PUPPIJet_SDSJnb1ecf2",          &AK8PUPPIJet_SDSJnb1ecf2_);
	tree->Branch("AK8PUPPIJet_SDSJnb1ecf3",          &AK8PUPPIJet_SDSJnb1ecf3);
	tree->Branch("AK8PUPPIJet_SDSJnb2ecf2",          &AK8PUPPIJet_SDSJnb2ecf2_);
	tree->Branch("AK8PUPPIJet_SDSJnb2ecf3",          &AK8PUPPIJet_SDSJnb2ecf3_);
}

void ggNtuplizer::fillAK8PUPPIJets(const edm::Event& e, const edm::EventSetup& es) {
	AK8PUPPIJet_Pt_.clear();
	AK8PUPPIJet_En_.clear();
	AK8PUPPIJet_RawPt_.clear();
	AK8PUPPIJet_RawEn_.clear();
	AK8PUPPIJet_Eta_.clear();
	AK8PUPPIJet_Phi_.clear();
	AK8PUPPIJet_Mass_.clear();
	AK8PUPPIJet_tau1_.clear();
	AK8PUPPIJet_tau2_.clear();
	AK8PUPPIJet_tau3_.clear();
	AK8PUPPIJet_CHF_.clear();
	AK8PUPPIJet_NHF_.clear();
	AK8PUPPIJet_CEF_.clear();
	AK8PUPPIJet_NEF_.clear();
	AK8PUPPIJet_NCH_.clear();
	AK8PUPPIJet_NNP_.clear();
	AK8PUPPIJet_MUF_.clear();
	AK8PUPPIJet_nconstituents_.clear();
	vector<Char_t> AK8PUPPIJet_PFid_.clear();
	AK8PUPPIJet_PUPPISoftDropMass_.clear();
	AK8PUPPIJet_CHSPrunedMass_.clear();
	AK8PUPPIJet_CHSSoftDropMass_.clear();
	AK8PUPPIJet_pfBoostedDSVBTag_.clear();
	AK8PUPPIJet_DSVnewV4_.clear();
	AK8PUPPIJet_CSV_.clear();
	AK8PUPPIJet_JECUnc_.clear();
	AK8PUPPIJet_L2L3corr_.clear();
	AK8PUPPIJet_JER_sf_.clear();
	AK8PUPPIJet_JER_sf_up_.clear();
	AK8PUPPIJet_JER_sf_down_.clear();
	AK8PUPPIJet_JER_ptRes_.clear();
	AK8PUPPIJet_JER_phiRes_.clear();
	AK8PUPPIJet_nb1ecf2_.clear();
	AK8PUPPIJet_nb1ecf3_.clear();
	AK8PUPPIJet_nb2ecf2_.clear();
	AK8PUPPIJet_nb2ecf3_.clear();
	AK8PUPPIJet_PartonFlavour_.clear();
	AK8PUPPIJet_HadronFlavour_.clear();
	AK8PUPPIJet_GenJetIndex_.clear();
	AK8PUPPIJet_GenPartonID_.clear();
	AK8PUPPIJet_GenPartonIndex_.clear();
	AK8PUPPIJet_GenJetEn_.clear();
	AK8PUPPIJet_GenJetPt_.clear();
	AK8PUPPIJet_GenJetEta_.clear();
	AK8PUPPIJet_GenJetPhi_.clear();
	AK8PUPPIJet_GenPartonID_.clear();
	nAK8PUPPIJet_SDSJ_ .clear();
	AK8PUPPIJet_SDSJPt_ .clear();
	AK8PUPPIJet_SDSJEta_ .clear();
	AK8PUPPIJet_SDSJMass_ .clear();
	AK8PUPPIJet_SDSJPhi_ .clear();
	AK8PUPPIJet_SDSJE_ .clear();
	AK8PUPPIJet_SDSJCharge_ .clear();
	AK8PUPPIJet_SDSJFlavour_.clear();
	AK8PUPPIJet_SDSJCSV_ .clear();
	AK8PUPPIJet_SDSJnb1ecf2_.clear();
	AK8PUPPIJet_SDSJnb1ecf3_.clear();
	AK8PUPPIJet_SDSJnb2ecf2_.clear();
	AK8PUPPIJet_SDSJnb2ecf3_.clear();

	nAK8PUPPIJet_ = 0;

	edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
	if(doGenParticles_)e.getByToken(genParticlesCollection_, genParticlesHandle);

	edm::Handle<double> rhoHandle;
	e.getByToken(rhoLabel_, rhoHandle);
	float rho = *(rhoHandle.product()); 

	edm::ESHandle<JetCorrectorParametersCollection> AK8JetCorParColl;
	es.get<JetCorrectionsRecord>().get("AK8PFchs",AK8JetCorParColl);
	JetCorrectorParameters const & AK8JetCorPar = (*AK8JetCorParColl)["Uncertainty"];
	JetCorrectionUncertainty *AK8jecUnc=0;
	AK8jecUnc = new JetCorrectionUncertainty(AK8JetCorPar);

	edm::Handle<edm::View<pat::Jet> > jetsAK8PUPPIhandle;
	e.getByToken(ak8JetsPUPPILabel_, jetsAK8PUPPIhandle);

	// Access JER
	JME::JetResolution jet_pt_resolution_ = JME::JetResolution::get(es, "AK8PFchs_pt");
	JME::JetResolution jet_phi_resolution_ = JME::JetResolution::get(es, "AK8PFchs_phi");
	JME::JetResolutionScaleFactor resolution_sf_ = JME::JetResolutionScaleFactor::get(es, "AK8PFchs");
	JME::JetParameters jet_parameters;

	for (edm::View<pat::Jet>::const_iterator ijetAK8 = jetsAK8PUPPIhandle->begin(); ijetAK8 != jetsAK8PUPPIhandle->end(); ++ijetAK8) {
		if( ijetAK8->pt() < 150.0 ) continue;

		nAK8PUPPIJet_++;
		AK8PUPPIJet_Pt_.push_back(ijetAK8->pt());
		AK8PUPPIJet_En_.push_back(ijetAK8->energy());
		AK8PUPPIJet_RawPt_.push_back(ijetAK8->correctedJet("Uncorrected").pt());
		AK8PUPPIJet_RawEn_.push_back(ijetAK8->correctedJet("Uncorrected").energy());
		AK8PUPPIJet_Eta_.push_back(ijetAK8->eta());
		AK8PUPPIJet_Phi_.push_back(ijetAK8->phi());
		AK8PUPPIJet_Mass_.push_back(ijetAK8->mass());
		AK8PUPPIJet_tau1_.push_back(ijetAK8->userFloat("NjettinessAK8Puppi:tau1"));
		AK8PUPPIJet_tau2_.push_back(ijetAK8->userFloat("NjettinessAK8Puppi:tau2"));
		AK8PUPPIJet_tau3_.push_back(ijetAK8->userFloat("NjettinessAK8Puppi:tau3"));
		AK8PUPPIJet_tau4_.push_back(ijetAK8->userFloat("NjettinessAK8Puppi:tau4"));
		AK8PUPPIJet_CHF_.push_back(ijetAK8->chargedHadronEnergyFraction());
		AK8PUPPIJet_NHF_.push_back(ijetAK8->neutralHadronEnergyFraction());
		AK8PUPPIJet_CEF_.push_back(ijetAK8->chargedEmEnergyFraction());
		AK8PUPPIJet_NEF_.push_back(ijetAK8->neutralEmEnergyFraction());
		AK8PUPPIJet_NCH_.push_back(ijetAK8->chargedMultiplicity());
		AK8PUPPIJet_NNP_.push_back(ijetAK8->neutralMultiplicity());
		AK8PUPPIJet_MUF_.push_back(ijetAK8->muonEnergyFraction());
		AK8PUPPIJet_nconstituents_.push_back(ijetAK8->chargedMultiplicity() + ijetAK8->neutralMultiplicity());

    	//jet PF Loose ID
		double NHF      = ijetAK8->neutralHadronEnergyFraction();
		double NEMF     = ijetAK8->neutralEmEnergyFraction();
		double NumConst = ijetAK8->chargedMultiplicity()+ijetAK8->neutralMultiplicity();
		double CHF      = ijetAK8->chargedHadronEnergyFraction();
		double CHM      = ijetAK8->chargedMultiplicity();
		double CEMF     = ijetAK8->chargedEmEnergyFraction();
		double NNP      = ijetAK8->neutralMultiplicity();
		double MUF      = ijetAK8->muonEnergyFraction();
      	//https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2017?rev=7
		bool looseJetID = false;    
		bool tightJetID = false;
		Bool_t tightLeptVetoID = false;
		if (fabs(iJet->eta()) <= 2.7) {
			looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(iJet->eta())>2.4);
			tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0) || fabs(iJet->eta())>2.4);
			tightLeptVetoID = (NHF<0.90 && NEMF<0.90 && NumConst>1 && MUF < 0.8) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.8) || fabs(iJet->eta())>2.4);
		} else if (fabs(iJet->eta()) <= 3.0) {
			looseJetID = (NEMF>0.01 && NHF<0.98 && NNP>2);
			tightJetID = (NEMF>0.02 && NEMF <0.99 && NNP>2);
			tightLeptVetoID = tightJetID;
		} else {
			looseJetID = (NEMF<0.90 && NNP>10); 
			tightJetID = (NEMF<0.90 && NNP>10 && NHF > 0.02);
			tightLeptVetoID = tightJetID;
		}
		Char_t jetIDdecision = 0;
		if(looseJetID) setbit(jetIDdecision, 0);
		if(tightJetID) setbit(jetIDdecision, 1);
		if(tightLeptVetoID) setbit(jetIDdecision, 2);
		AK8PUPPIJet_PFid_.push_back(jetIDdecision);

		AK8PUPPIJet_PUPPISoftDropMass_.push_back(ijetAK8->userFloat("ak8PFJetsPuppiSoftDropMass"));
		AK8PUPPIJet_CHSPrunedMass_.push_back(ijetAK8->userFloat("ak8PFJetsCHSValueMap:ak8PFJetsCHSPrunedMass");
		AK8PUPPIJet_CHSSoftDropMass_.push_back(ijetAK8->userFloat("ak8PFJetsCHSValueMap:ak8PFJetsCHSSoftDropMass");

		AK8PUPPIJet_pfBoostedDSVBTag_.push_back(ijetAK8->);
		AK8PUPPIJet_DSVnewV4_.push_back(ijetAK8->);
		AK8PUPPIJet_CSV_.push_back(ijetAK8->);
		AK8PUPPIJet_JECUnc_.push_back(ijetAK8->);
		AK8PUPPIJet_L2L3corr_.push_back(ijetAK8->);
		AK8PUPPIJet_JER_sf_.push_back(ijetAK8->);
		AK8PUPPIJet_JER_sf_up_.push_back(ijetAK8->);
		AK8PUPPIJet_JER_sf_down_.push_back(ijetAK8->);
		AK8PUPPIJet_JER_ptRes_.push_back(ijetAK8->);
		AK8PUPPIJet_JER_phiRes_.push_back(ijetAK8->);
		AK8PUPPIJet_nb1ecf2_.push_back(ijetAK8->);
		AK8PUPPIJet_nb1ecf3_.push_back(ijetAK8->);
		AK8PUPPIJet_nb2ecf2_.push_back(ijetAK8->);
		AK8PUPPIJet_nb2ecf3_.push_back(ijetAK8->);
		AK8PUPPIJet_PartonFlavour_.push_back(ijetAK8->);
		AK8PUPPIJet_HadronFlavour_.push_back(ijetAK8->);
		AK8PUPPIJet_GenJetIndex_.push_back(ijetAK8->);
		AK8PUPPIJet_GenPartonID_.push_back(ijetAK8->);
		AK8PUPPIJet_GenPartonIndex_.push_back(ijetAK8->);
		AK8PUPPIJet_GenJetEn_.push_back(ijetAK8->);
		AK8PUPPIJet_GenJetPt_.push_back(ijetAK8->);
		AK8PUPPIJet_GenJetEta_.push_back(ijetAK8->);
		AK8PUPPIJet_GenJetPhi_.push_back(ijetAK8->);
		AK8PUPPIJet_GenPartonID_.push_back(ijetAK8->);

	}
}