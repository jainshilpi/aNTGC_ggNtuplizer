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


workarea='/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/crab_submit/testJobs//aNTGC_0p0008_0p_0p_0p_300_350/'

mainOutputDir = '#mainOutputDir'


config.General.requestName = 'aNTGC_0p0008_0p_0p_0p_300_350'
config.General.transferLogs = True
config.General.workArea = '%s' % workarea


config.Site.storageSite = 'T2_US_Wisconsin'
config.Site.whitelist = ['T3_US_FNALLPC']
config.Site.blacklist = ['T2_US_Florida','T2_US_Vanderbilt','T3_US_PuertoRico','T2_US_Caltech']


config.JobType.psetName  = '/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/run_mc2017_94X.py'
config.JobType.pluginName  = 'Analysis'


config.Data.inputDBS = '#inputDBS'
config.Data.inputDataset = '/aNTGC_0p0008_0p_0p_0p_300_350/mwadud-aNTGC_0p0008_0p_0p_0p_300_350_MINIAODSIM-8b3f0a6dce9f2bd2c845840a26003c60/USER'
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Data.outLFNDirBase = '%s' % mainOutputDir
config.Data.splitting     = 'FileBased'
config.Data.unitsPerJob   = #unitsperjob
config.Data.ignoreLocality = False
#config.Data.totalUnits = #totalUnits
submit(config)
