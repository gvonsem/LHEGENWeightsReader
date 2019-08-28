Based on [repository](https://github.com/lviliani/LHEWeightsReader) of Lorenzo Viliani to read and dump LHE weights (scale, PDF) from MiniAOD files, and extended to include functionality to read and dump GEN weights (parton shower)

The following instructions were tested on lxplus.

#Installation

```
export SCRAM_ARCH=slc7_amd64_gcc700  
cmsrel CMSSW_10_2_3
cd CMSSW_10_2_3/src
cmsenv   
mkdir LHEGENWeightsReader  
cd LHEGENWeightsReader
git clone https://github.com/gvonsem/LHEGENWeightsReader.git
scram b
cd LHEGENWeightsReader/test/
```

#Running

```
cd LHEGENWeightsReader/test/
```

Script to print out (per run) the header of the LHERunInfoProduct, to see which LHE weights (scale, PDF) are available in the file.

```
cmsRun lheWeightReader_cfg.py inputFiles="MINIAOD_FILE"
```

Script to print out (per event) the weights in LHEEventProduct, to see the values of the LHE weights (scale, PDF) available in the file.

```
cmsRun lheWeightDumper_cfg.py inputFiles="MINIAOD_FILE"
```

Script to print out (per lumisection) the weight names in GenLumiInfoHeader, to see which GEN weights (PS) are available in the file.

```
cmsRun genWeightReader_cfg.py inputFiles="MINIAOD_FILE"
```

Script to print out (per event) the weights in GenEventInfoProduct, to see the values of the GEN weights (PS) available in the file.

```
cmsRun genWeightDumper_cfg.py inputFiles="MINIAOD_FILE"
```

#Example ro accessing MiniAOD remotely

In order to read a file found in DAS remotely, one can make use of the [Xrootd service](https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookXrootdService).
```
# create proxy
voms-proxy-init -voms cms

cmsRun lheWeightDumper_cfg.py inputFiles="root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18MiniAOD/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/270000/FFDD758E-EA75-A34C-9941-FB06C26375A2.root"
```
