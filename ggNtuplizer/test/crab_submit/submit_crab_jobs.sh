#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh;
eval `scramv1 runtime -sh`;
voms-proxy-init --voms cms

input_datasets="datasets.txt"
writedir="/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/crab_submit/jobs"
psetname="/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/run_mc2017_94X.py"
writeSite="T2_US_Wisconsin"


crab_cfg_template=crab_submit.py
units_perjob=10
splitting='FileBased'
blacklist="'T2_US_Florida','T2_US_Vanderbilt','T3_US_PuertoRico'"
# whitelist="'T3_US_UCR','T3_US_FNALLPC','T2_US_Purdue','T3_US_Rice','T3_US_Cornell','T3_US_Rutgers','T3_US_FIU','T3_US_FIT','T3_US_PSC','T3_US_OSU','T3_US_TAMU','T3_US_UMD','T2_US_Caltech','T3_US_VC3_NotreDame','T3_US_SDSC','T3_US_Colorado','T3_US_OSG','T3_US_Princeton_ICSE','T3_US_NERSC','T3_US_Baylor','T2_US_Nebraska','T2_US_UCSD','T2_US_Wisconsin','T2_US_MIT','T3_US_TACC','T3_US_TTU','T3_US_UMiss'"

submit_log_file=${writedir}/crab_submitted_datasets_$(date '+%d_%m_%Y_%H_%M_%S').log

mkdir -p ${writedir}
for dataset in `sed '/^$/d' ${input_datasets}`;
do
	datasetName=$(echo ${dataset} | cut -f1,2 -d'/')
	# jobName=${datasetName#"/"}_$(date '+%d_%m_%Y_%H_%M_%S');
	jobName=${datasetName#"/"}

	jobDir=${writedir}/${jobName}/

	echo "Submitting " ${jobName}
	echo "Job directory: "${jobDir}
	echo "Write site: " ${writeSite}

	# if [ -d "$jobDir" ]; then
	# 	echo "Error! Directory "$jobDir "exists!" 
 #  		exit
	# fi

	rm -rf ${jobDir}

	mkdir -p ${jobDir}

	crab_cfg_file=${jobDir}/crab_${jobName}.py
	cp ${crab_cfg_template} ${crab_cfg_file}

	sed -i 's|#psetname|'$psetname'|g' ${crab_cfg_file}
	sed -i 's|#workarea|'$jobDir'|g' ${crab_cfg_file}
	sed -i 's|#jobname|'$jobName'|g' ${crab_cfg_file}
	sed -i 's|#inputDataset|'$dataset'|g' ${crab_cfg_file}
	sed -i 's|#storageSite|'$writeSite'|g' ${crab_cfg_file}
	# sed -i 's|#whitelist|'$whitelist'|g' ${crab_cfg_file}
	sed -i 's|#blacklist|'$blacklist'|g' ${crab_cfg_file}
	sed -i 's|#splitting|'$splitting'|g' ${crab_cfg_file}
	sed -i 's|#unitsperjob|'$units_perjob'|g' ${crab_cfg_file}

	python ${crab_cfg_file} | tee ${submit_log_file}
done