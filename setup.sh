#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh;

export CMSSW_GIT_REFERENCE=/afs/cern.ch/cms/git-cmssw-mirror/cmssw.git

scramv1 project CMSSW CMSSW_9_4_13
cd CMSSW_9_4_13/src 
scramv1 runtime -sh;
git cms-init 
git cms-addpkg CondFormats/JetMETObjects 
git cms-addpkg JetMETCorrections/Modules 
git cms-addpkg RecoBTag/Combined 
git cms-addpkg JetMETCorrections/Type1MET 
git cms-addpkg RecoMET/METFilters 
git cms-addpkg RecoEgamma/PostRecoTools 
git cms-addpkg RecoEgamma/PhotonIdentification/ 
git cms-addpkg RecoEgamma/ElectronIdentification/ 
git cms-addpkg CommonTools/PileupAlgos 
scram b -j 8 
git cms-merge-topic cms-egamma:EgammaPostRecoTools 
scram b -j 8 
git cms-merge-topic cms-met:METFixEE2017_949_v2 
scram b -j 8 
git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_94X_v4 
scram b -j 8 
git clone -b master --single-branch git@github.com:wadud001/aNTGC_gggNtuplizer.git <br> --depth 1
scram b -j8 
