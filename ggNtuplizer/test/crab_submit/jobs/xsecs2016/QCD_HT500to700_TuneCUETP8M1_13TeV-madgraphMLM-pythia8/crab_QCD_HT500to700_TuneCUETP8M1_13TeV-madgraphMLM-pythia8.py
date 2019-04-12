from CRABClient.UserUtilities import config, getUsernameFromSiteDB
import sys

config = config()


#**************************submit function***********************
from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException
def submit(config):
	try:
		crabCommand('submit', config = config)
	except HTTPException as hte:
		print "Failed submitting task: %s" % (hte.headers)
	except ClientException as cle:
		print "Failed submitting task: %s" % (cle)
#****************************************************************


workarea='/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/crab_submit/jobs/xsecs2016//QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'

mainOutputDir = '/store/user/mwadud/aNTGC/ggNtuplizerSkim/xSecs/'


config.General.requestName = 'QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
config.General.transferLogs = True
config.General.workArea = '%s' % workarea


config.Site.storageSite = 'T2_US_Wisconsin'
config.Site.whitelist = ['T3_US_FNALLPC']
config.Site.blacklist = []


config.JobType.psetName  = '/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/crab_submit/XsecAna.py'
config.JobType.pluginName  = 'Analysis'


config.Data.inputDBS = 'global'
config.Data.inputDataset = '/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM'
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Data.outLFNDirBase = '%s' % mainOutputDir
config.Data.splitting     = 'FileBased'
config.Data.unitsPerJob   = 10
config.Data.ignoreLocality = True
#config.Data.totalUnits = #totalUnits
submit(config)
