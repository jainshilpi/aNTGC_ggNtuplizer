Steps:
cmsrel CMSSW_9_4_13 <br>
cd CMSSW_9_4_13/src <br>
cmsenv <br>
git cms-init <br>
git cms-addpkg CondFormats/JetMETObjects
git cms-addpkg JetMETCorrections/Modules
git cms-addpkg RecoBTag/Combined
git cms-addpkg JetMETCorrections/Type1MET
git cms-addpkg RecoMET/METFilters
git cms-addpkg RecoEgamma/PostRecoTools
git cms-addpkg RecoEgamma/PhotonIdentification/
git cms-addpkg RecoEgamma/ElectronIdentification/
git cms-addpkg CommonTools/PileupAlgos
scram b -j 8 <br>
git cms-merge-topic cms-egamma:EgammaPostRecoTools <br>
scram b -j 8 <br>
git cms-merge-topic cms-met:METFixEE2017_949_v2 <br>
scram b -j 8 <br>
cd $CMSSW_BASE/src <br>
git clone -b 94X git@github.com:wadud001/aNTGC_gggNtuplizer.git <br>
scram b -j8 <br>

