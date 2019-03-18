Steps:
======
cmsrel CMSSW_9_4_13 <br> 

cd CMSSW_9_4_13/src <br>

cmsenv <br>

git cms-init <br>

git cms-addpkg CondFormats/JetMETObjects <br> 

git cms-addpkg JetMETCorrections/Modules <br> 

git cms-addpkg RecoBTag/Combined <br> 

git cms-addpkg JetMETCorrections/Type1MET <br> 

git cms-addpkg RecoMET/METFilters <br> 

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

git clone -b 94X git@github.com:wadud001/aNTGC_gggNtuplizer.git <br>

scram b -j8 <br>

