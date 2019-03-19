#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh;
export CMSSW_GIT_REFERENCE=/afs/cern.ch/cms/git-cmssw-mirror/cmssw.git
presentDir=$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )
cd $presentDir
eval 'scramv1 project CMSSW CMSSW_9_4_13'
source /cvmfs/cms.cern.ch/cmsset_default.sh;
cd ${presentDir}/CMSSW_9_4_13/src
eval `scramv1 runtime -sh`;
git cms-init
git cms-addpkg CondFormats/JetMETObjects 
git cms-addpkg JetMETCorrections/Modules
git config merge.renamelimit 15345
git cms-addpkg RecoBTag/Combined
git cms-addpkg JetMETCorrections/Type1MET
git cms-addpkg RecoMET/METFilters
git cms-addpkg RecoEgamma/PhotonIdentification
git cms-addpkg RecoEgamma/ElectronIdentification
git cms-addpkg CommonTools/PileupAlgos
cd $CMSSW_BASE
git cms-merge-topic cms-egamma:EgammaPostRecoTools
cd $CMSSW_BASE
git cms-merge-topic cms-met:METFixEE2017_949_v2
cd $CMSSW_BASE
git clone https://github.com/cms-jet/JetToolbox.git -b jetToolbox_94X_v4
cd $CMSSW_BASE
git clone -b master https://github.com/wadud001/aNTGC_gggNtuplizer.git
mv aNTGC_gggNtuplizer ggAnalysis
ls
scram b -j 20
