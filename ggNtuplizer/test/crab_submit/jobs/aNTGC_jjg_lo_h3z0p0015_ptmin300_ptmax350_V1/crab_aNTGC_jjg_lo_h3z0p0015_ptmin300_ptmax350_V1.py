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


workarea='/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/crab_submit/jobs/aNTGC_jjg_lo_h3z0p0015_ptmin300_ptmax350_V1/'

mainOutputDir = '/store/user/mwadud/aNTGC/ggNtuplizerSkim/'


config.General.requestName = 'aNTGC_jjg_lo_h3z0p0015_ptmin300_ptmax350_V1'
config.General.transferLogs = True
config.General.workArea = '%s' % workarea


config.Site.storageSite = 'T2_US_Wisconsin'
config.Site.whitelist = ['T3_US_FNALLPC']
config.Site.blacklist = []


config.JobType.psetName  = '/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/run_mc2017_94X.py'
config.JobType.pluginName  = 'Analysis'


config.Data.inputDBS = 'phys03'
config.Data.inputDataset = '/aNTGC_jjg_lo_h3z0p0015_ptmin300_ptmax350_V1/mwadud-jjg_lo_h3z0p0015_ptmin300_ptmax350_MINIAODSIM_V1-c713347d19aab94d9d4f2cb9b9611348/USER'
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Data.outLFNDirBase = '%s' % mainOutputDir
config.Data.splitting     = 'FileBased'
config.Data.unitsPerJob   = 10
config.Data.ignoreLocality = True
#config.Data.totalUnits = #totalUnits
submit(config)
