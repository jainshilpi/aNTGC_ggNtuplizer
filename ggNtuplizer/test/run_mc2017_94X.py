import FWCore.ParameterSet.Config as cms

process = cms.Process('ggKit')

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v17')

#process.Tracer = cms.Service("Tracer")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(20) )
process.MessageLogger.cerr.FwkReport.reportEvery = 5000

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    # 'file:4ABBDF87-C443-E811-B7FB-00259022516E.root'
    # 'file:049CDDCC-4741-E911-BAF6-0025905A60AA.root'
    'file:sherpa_jjg_lo_h3z0p0003_ptmin500_ptmax550_MASTER_cff_py_MINIAODSIM_38.root'
    ))

#process.load("PhysicsTools.PatAlgos.patSequences_cff")

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

### fix a bug in the ECAL-Tracker momentum combination when applying the scale and smearing
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
 runVID=True,
 era='2017-Nov17ReReco',
 eleIDModules=['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
 'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
 'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff',
 'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V2_cff'],
 phoIDModules=['RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V2_cff',
 'RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_cff']
 )

process.TFileService = cms.Service("TFileService", fileName = cms.string('anTGCtree_mc.root'))

### reduce effect of high eta EE noise on the PF MET measurement
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD (
  process,
        isData = False, # false for MC
        fixEE2017 = True,
        fixEE2017Params = {'userawPt': True, 'ptThreshold':50.0, 'minEtaThreshold':2.65, 'maxEtaThreshold': 3.139} ,
        postfix = "ModifiedMET"
        )

### include jetToolbox to add various jets
from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox

### ak0.4CHSjets
# jetToolbox( process, 'ak4', 'ak4CHSJetToolbox', 'noOutput',
#             # PUMethod='CHS',
#             updateCollection='slimmedJets',
#             # addPruning=True,
#             # addPrunedSubjets=True,
#             # addTrimming=True,
#             # addFiltering=True,
#             # addNsub=True,
#             # maxTau=3,
#             addQGTagger=True,
#             # addPUJetID=True,
#             # addEnergyCorrFunc=True,
#             JETCorrPayload = 'AK4PFchs',
#             JETCorrLevels = ['L1FastJet', 'L2Relative', 'L3Absolute']
#             )

jetToolbox( process, 'ak4', 'ak4JetSubs', 'noOutput',
        updateCollection='slimmedJets',
        JETCorrPayload='AK4PFchs',
        JETCorrLevels = ['L1FastJet', 'L2Relative', 'L3Absolute'],
        postFix='updated'
        )

### ak 0.8 PUPPI jets
jetToolbox( process, 'ak8', 'ak8PUPPIJetToolbox', 'noOutput',
            PUMethod='PUPPI',
            updateCollection='slimmedJetsAK8',
            updateCollectionSubjets='slimmedJetsAK8PFPuppiSoftDropPacked',
            JETCorrPayload = 'AK8PFPuppi'
            # subJETCorrPayload='AK4PFPuppi'
            # addPruning=True,
            # addSoftDrop=True
            # addTrimming=True,
            # addFiltering=True,
            # addNsub=True,
            # maxTau=3,
            # addQGTagger=True,
            # addPUJetID=True,
            # addEnergyCorrFunc=True
            )

process.load("ggAnalysis.ggNtuplizer.ggNtuplizer_miniAOD_cfi")
process.ggNtuplizer.year=cms.int32(2017)
process.ggNtuplizer.doGenParticles=cms.bool(True)
process.ggNtuplizer.dumpPFPhotons=cms.bool(False)
process.ggNtuplizer.dumpHFElectrons=cms.bool(False)
process.ggNtuplizer.dumpJets=cms.bool(True)
process.ggNtuplizer.dumpAK8Jets=cms.bool(True)
process.ggNtuplizer.dumpSoftDrop= cms.bool(True)
process.ggNtuplizer.dumpTaus=cms.bool(False)
# process.ggNtuplizer.triggerEvent=cms.InputTag("slimmedPatTrigger", "", "PAT")
process.ggNtuplizer.ak4PFJetsCHSSrc=cms.InputTag("selectedPatJetsAK4PFCHSupdated")
process.ggNtuplizer.ak4PFJetsCHSGenJetLabel      = cms.InputTag("selectedPatJetsAK4PFCHSupdated","genJets","ggKit")
process.ggNtuplizer.ak8JetsPUPPISrc=cms.InputTag("selectedPatJetsAK8PFPUPPI")
process.ggNtuplizer.runOnSherpa = cms.bool(True)
patTriggerResults    = cms.InputTag("TriggerResults", "", "RECO")
process.ggNtuplizer.triggerEvent=cms.InputTag("slimmedPatTrigger")

process.p = cms.Path(
  process.fullPatMetSequenceModifiedMET *
  process.egammaPostRecoSeq *
  process.ggNtuplizer
  )

#print process.dumpPython()
