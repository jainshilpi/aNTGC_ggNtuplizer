Step 1: Set Up CMSSW 
====================
**To skip this step, download setup.sh and run it in the desired directory.**<br> 
export CMSSW_GIT_REFERENCE=/afs/cern.ch/cms/git-cmssw-mirror/cmssw.git <br> 
cmsrel CMSSW_9_4_13 <br> 
cd CMSSW_9_4_13/src <br>
cmsenv <br>
git cms-init <br>
git cms-addpkg CondFormats/JetMETObjects <br> 
git cms-addpkg JetMETCorrections/Modules <br> 
git cms-addpkg RecoBTag/Combined <br> 
git cms-addpkg JetMETCorrections/Type1MET <br> 
git cms-addpkg RecoMET/METFilters <br>
git cms-merge-topic cms-egamma:EgammaPostRecoTools<br>
git cms-addpkg RecoEgamma/PostRecoTools <br> 
git cms-addpkg RecoEgamma/PhotonIdentification/ <br> 
git cms-addpkg RecoEgamma/ElectronIdentification/ <br> 
git cms-addpkg CommonTools/PileupAlgos <br> 
scram b -j 8 <br>
git cms-merge-topic cms-egamma:EgammaPostRecoTools <br>
scram b -j 8 <br>
git cms-merge-topic cms-met:METFixEE2017_949_v2 <br>
scram b -j 8 <br>
git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_94X_v4 <br> 
scram b -j 8 <br>
git clone -b master git@github.com:wadud001/aNTGC_gggNtuplizer.git <br>
mv aNTGC_gggNtuplizer ggAnalysis
scram b -j8 <br>


Step 2: Edit crab script & submit
=================================
cd $CMSSW_BASE/src/ggAnalysis/ggNtuplizer/test/crab_submit/<br>
Open submit_crab_jobs.sh in text editor <br>
Modify the variables: <br>
* *input_datasets* - text file listing datasets <br>
* *writedir* - common directory for temporary crab files <br>
* *psetname* - python script for cmsRun <br>
* *writeSite* - site to write crab jobs <br>
* *mainOutputDir* - path to write crab outputs <br>

___Submit___ ./submit_crab_jobs.sh<br>
A log file named *crab_submitted_datasets_[date-time].log* will be created in *writedir* for the submissions. <br>


Step 3: Resubmit failed jobs
============================
./resubmit_crab_jobs __[log file from previous step]__
