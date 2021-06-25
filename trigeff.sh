
ONIAFILEPATH="../rootfiles/datasets/Run3Pre_dilepton/Oniatree_MC_miniAOD_PG_Pt_0p5_3_5p02TeV_cmssw11_2_2_Run3Cond_merged.root"
TRIGGERFILEPATH="../rootfiles/datasets/Run3Prep_DileptonHLT_2021/openHLT_Run3HLT_Dilepton_MC_Pt_0p5_100.root"
TRIGGERNAME="HLT_HIL1SingleMu0Open_v1"

./TrigEff/trigeff ${ONIAFILEPATH} ${TRIGGERFILEPATH} ${TRIGGERNAME}