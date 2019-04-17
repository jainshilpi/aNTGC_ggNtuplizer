#!/bin/bash

input_datasets="datasets.txt"
# input_datasets="2016_mc_samples.txt"
writedir="/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/crab_submit/jobsUpdatedAnalyzer/"
psetname="/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/run_mc2017_94X.py"
# psetname="/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/crab_submit/XsecAna.py"
writeSite="T2_US_Wisconsin"
mainOutputDir='/store/user/mwadud/aNTGC/ggNtuplizerSkimV2/'


maxFiles=5000
inputDBS=global


################################################################################################################
source /cvmfs/cms.cern.ch/cmsset_default.sh;
source /cvmfs/cms.cern.ch/crab3/crab.sh;
eval `scramv1 runtime -sh`;
voms-proxy-init --voms cms


crab_cfg_template=crab_submit.py
units_perjob=5
splitting='FileBased'
blacklist="'T2_US_Florida','T2_US_Vanderbilt','T3_US_PuertoRico','T2_US_Caltech'"
whitelist="'T3_US_UCR','T3_US_FNALLPC','T2_US_Purdue','T3_US_Rice','T3_US_Cornell','T3_US_Rutgers','T3_US_FIU','T3_US_FIT','T3_US_PSC','T3_US_OSU','T3_US_TAMU','T3_US_UMD','T3_US_VC3_NotreDame','T3_US_SDSC','T3_US_Colorado','T3_US_OSG','T3_US_Princeton_ICSE','T3_US_NERSC','T3_US_Baylor','T2_US_Nebraska','T2_US_UCSD','T2_US_Wisconsin','T2_US_MIT','T3_US_TACC','T3_US_TTU','T3_US_UMiss'"
# blacklist=""
# whitelist="'T3_US_FNALLPC'"

mkdir -p ${writedir}
submit_log_file=${writedir}/crab_submitted_datasets_$(date '+%d_%m_%Y_%H_%M_%S').log

echo "*************************************************************************" | tee --append ${submit_log_file}
echo "Git Info" | tee --append ${submit_log_file}
git remote -v | tee --append ${submit_log_file}
git branch -a | tee --append ${submit_log_file}
git rev-parse HEAD | tee --append ${submit_log_file}
echo "*************************************************************************" | tee --append ${submit_log_file}


for dataset in `sed '/^$/d' ${input_datasets}`;
do
	datasetName=$(echo ${dataset} | cut -f1,2 -d'/')
	jobName=${datasetName#"/"}

	# jobName=$(echo ${dataset////_})
	# jobName=${jobName#"_"}

	jobDir=${writedir}/${jobName}/

	echo "Submitting " ${jobName}
	echo "Job directory: "${jobDir}
	echo "Write site: " ${writeSite}

	if [ -d "$jobDir" ]; then
		echo "Error! Directory "$jobDir "exists!"
		exit
	fi

	mkdir -p ${jobDir}

	crab_cfg_file=${jobDir}/crab_${jobName}.py
	cp ${crab_cfg_template} ${crab_cfg_file}

	sed -i 's|#psetname|'$psetname'|g' ${crab_cfg_file}
	sed -i 's|#workarea|'$jobDir'|g' ${crab_cfg_file}
	sed -i 's|#jobname|'$jobName'|g' ${crab_cfg_file}
	sed -i 's|#inputDataset|'$dataset'|g' ${crab_cfg_file}
	sed -i 's|#storageSite|'$writeSite'|g' ${crab_cfg_file}
	sed -i 's|#whitelist|'$whitelist'|g' ${crab_cfg_file}
	sed -i 's|#blacklist|'$blacklist'|g' ${crab_cfg_file}
	sed -i 's|#splitting|'$splitting'|g' ${crab_cfg_file}
	sed -i 's|#unitsperjob|'$units_perjob'|g' ${crab_cfg_file}
	sed -i 's|#mainOutputDir|'$mainOutputDir'|g' ${crab_cfg_file}

	sed -i 's|#inputDBS|'$inputDBS'|g' ${crab_cfg_file}


	# sed -i 's|#config.Data.totalUnits|'config.Data.totalUnits'|g' ${crab_cfg_file}
	# sed -i 's|#totalUnits|'$maxFiles'|g' ${crab_cfg_file}

	python ${crab_cfg_file} | tee --append ${submit_log_file}
done
