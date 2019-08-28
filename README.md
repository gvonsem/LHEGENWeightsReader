The following instructions were tested on lxplus.

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

Script to print out (per run) the header of the LHERunInfoProduct, to see which LHE weights (scale, PDF) are available in the file.

```
cmsRun lheWeightReader_cfg.py inputFiles="MINIAOD_FILE"
```

Script to print out (per event) the weights in LHEEventProduct, to see the values of the LHE weights (scale, PDF) available in the file.

```
cmsRun lheWeightDumper_cfg.py inputFiles="MINIAOD_FILE"
```
