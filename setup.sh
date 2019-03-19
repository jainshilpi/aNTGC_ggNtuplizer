#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh;

export CMSSW_GIT_REFERENCE=/afs/cern.ch/cms/git-cmssw-mirror/cmssw.git

presentDir=$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )
eval 'scramv1 project CMSSW CMSSW_9_4_13'
cd ${presentDir}/CMSSW_9_4_13/src
source /cvmfs/cms.cern.ch/cmsset_default.sh;
eval `scramv1 runtime -sh`;
git cms-init
git cms-addpkg CondFormats/JetMETObjects 
git cms-addpkg JetMETCorrections/Modules
git config merge.renamelimit 15345
git cms-addpkg RecoBTag/Combined
git cms-addpkg JetMETCorrections/Type1MET
git cms-addpkg RecoMET/METFilters
git cms-addpkg RecoEgamma/PostRecoTools
git cms-addpkg RecoEgamma/PhotonIdentification
git cms-addpkg RecoEgamma/ElectronIdentification
git cms-addpkg CommonTools/PileupAlgos
cd $CMSSW_BASE
git cms-merge-topic cms-egamma:EgammaPostRecoTools
cd $CMSSW_BASE
git cms-merge-topic cms-met:METFixEE2017_949_v2
cd $CMSSW_BASE
git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_94X_v4
cd $CMSSW_BASE
git clone -b master git@github.com:wadud001/aNTGC_gggNtuplizer.git
mv aNTGC_gggNtuplizer ggAnalysis
ls
scram b -j 20
