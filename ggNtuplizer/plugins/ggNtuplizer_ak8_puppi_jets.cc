#include "FWCore/MessageLogger/interface/MessageLogger.h"
// #include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/RandGauss.h"

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

vector<float> AK8PUPPIJet__tau1_;
vector<float> AK8PUPPIJet__tau2_;
vector<float> AK8PUPPIJet__tau3_;

vector<float> AK8PUPPIJet_CHF_;
vector<float> AK8PUPPIJet_NHF_;
vector<float> AK8PUPPIJet_CEF_;
vector<float> AK8PUPPIJet_NEF_;
vector<int>   AK8PUPPIJet_NCH_;
vector<int>   AK8PUPPIJet_NNP_;
vector<float> AK8PUPPIJet_MUF_;
vector<int>   AK8PUPPIJet_nconstituents_;

vector<bool>  AK8PUPPIJet_PFLooseId_;
vector<bool>  AK8PUPPIJet_PFTightLepVetoId_;

vector<float> AK8PUPPIJet_SoftDropMass_;
vector<float> AK8PUPPIJet_SoftDropMassCorr_;

vector<float> AK8PUPPIJet_PrunedMass_;
vector<float> AK8PUPPIJet_PrunedMassCorr_;

vector<float> AK8PUPPIJet_pfBoostedDSVBTag_;
vector<float> AK8PUPPIJet_DSVnewV4_;
vector<float> AK8PUPPIJet_CSV_;

vector<float> AK8PUPPIJet_JECUnc_;
vector<float> AK8PUPPIJet_L2L3corr_;

//gen-info for ak8

vector<int>   AK8PUPPIJet_PartonID_;
vector<int>   AK8PUPPIJet_HadFlvr_;
vector<int>   AK8PUPPIJet_GenJetIndex_;
vector<float> AK8PUPPIJet_GenJetEn_;
vector<float> AK8PUPPIJet_GenJetPt_;
vector<float> AK8PUPPIJet_GenJetEta_;
vector<float> AK8PUPPIJet_GenJetPhi_;
vector<int>   AK8PUPPIJet_GenPartonID_;
vector<float> AK8PUPPIJet_GenEn_;
vector<float> AK8PUPPIJet_GenPt_;
vector<float> AK8PUPPIJet_GenEta_;
vector<float> AK8PUPPIJet_GenPhi_;
vector<int>   AK8PUPPIJet_GenPartonMomID_;

vector<float> AK8PUPPIJet_P4Smear_;
vector<float> AK8PUPPIJet_P4SmearUp_;
vector<float> AK8PUPPIJet_P4SmearDo_;

//soft drop subjets
vector<int>             nAK8SDSJ_ ;
vector< vector<float> > AK8SDSJPt_ ;
vector< vector<float> > AK8SDSJEta_ ;
vector< vector<float> > AK8SDSJMass_ ;
vector< vector<float> > AK8SDSJPhi_ ;
vector< vector<float> > AK8SDSJE_ ;
vector< vector<int > >  AK8SDSJCharge_ ;
vector< vector<int > >  AK8SDSJFlavour_;
vector< vector<float> > AK8SDSJCSV_ ;

//puppi
vector<float> AK8puppiPt_;
vector<float> AK8puppiMass_;
vector<float> AK8puppiEta_;
vector<float> AK8puppiPhi_;
//vector<float> AK8puppiTau1_;
//vector<float> AK8puppiTau2_;
//vector<float> AK8puppiTau3_;
vector<float> AK8puppiSDL2L3corr_;
vector<float> AK8puppiSDMass_;
vector<float> AK8puppiSDMassL2L3Corr_;

//puppi + soft drop subjets
vector<int>             nAK8puppiSDSJ_ ;
vector< vector<float> > AK8puppiSDSJPt_ ;
vector< vector<float> > AK8puppiSDSJEta_ ;
vector< vector<float> > AK8puppiSDSJMass_ ;
vector< vector<float> > AK8puppiSDSJPhi_ ;
vector< vector<float> > AK8puppiSDSJE_ ;
vector< vector<int > >  AK8puppiSDSJCharge_ ;
vector< vector<int > >  AK8puppiSDSJFlavour_;
vector< vector<float> > AK8puppiSDSJCSV_ ;


