
#path to onia file
ONIAFILEPATH="../rootfiles/datasets/Run3Pre_dilepton/Oniatree_MC_miniAOD_PG_Pt_0p5_3_5p02TeV_cmssw11_2_2_Run3Cond_merged.root"
#path to trigger file
TRIGGERFILEPATH="../rootfiles/datasets/Run3Prep_DileptonHLT_2021/openHLT_Run3HLT_Dilepton_MC_Pt_0p5_100.root"
#name of the trigger inside trigger file
TRIGGERNAME="HLT_HIL1SingleMu0Open_v1"
#path to directory to place output
OUTPUTPATH="../rootfiles/analysis/triggerStudy"

mkdir ${OUTPUTPATH}

./TrigEff/trigeff ${ONIAFILEPATH} ${TRIGGERFILEPATH} ${TRIGGERNAME} ${OUTPUTPATH}