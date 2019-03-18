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


workarea='/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/crab_submit/jobs/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/'

mainOutputDir = '/store/user/mwadud/aNTGC/ggNtuplizerSkim/'


config.General.requestName = 'QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8'
config.General.transferLogs = True
config.General.workArea = '%s' % workarea


config.Site.storageSite = 'T2_US_Wisconsin'
# config.Site.whitelist = [#whitelist]
config.Site.blacklist = ['T2_US_Florida','T2_US_Vanderbilt','T3_US_PuertoRico']


config.JobType.psetName  = '/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/run_mc2017_94X.py'
config.JobType.pluginName  = 'Analysis'


config.Data.inputDataset = '/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM'
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Data.outLFNDirBase = '%s' % mainOutputDir
config.Data.splitting     = 'FileBased'
config.Data.unitsPerJob   = 10
# config.Data.ignoreLocality = True

submit(config)
