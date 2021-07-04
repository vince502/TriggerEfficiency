
#path to onia file
ONIAFILEPATH=${1:-"../rootfiles/datasets/Run3Pre_dilepton/Oniatree_MC_miniAOD_PG_Pt_3_100_Hydjet_5p02TeV_cmssw11_2_2_Run3Cond_merged.root"}
#path to trigger file
TRIGGERFILEPATH=${2:-"../rootfiles/datasets/Run3Prep_DileptonHLT_2021/openHLT_Run3HLT_Dilepton_MC_Pt_0p5_100.root"}
#name of the trigger inside trigger file
TRIGGERNAME=${3:-"HLT_HIL1SingleMu0_v1"}
#path to directory to place output
OUTPUTPATH=${4:-"../rootfiles/analysis/triggerStudy/HLT_HIL1SingleMu0_v1"}
#pt range, lowpt or highpt
PTRANGE=${5:-"highpt"}

mkdir -p ${OUTPUTPATH}

echo "Trigger efficiency study"

echo "reading reco file '${ONIAFILEPATH}'"
echo "reading hltobj file '${TRIGGERFILEPATH}'"

echo "output to:"
echo "  ${OUTPUTPATH}/$( basename $ONIAFILEPATH)"

./TrigEff/trigeff ${ONIAFILEPATH} ${TRIGGERFILEPATH} ${TRIGGERNAME} $OUTPUTPATH
echo "generating plots for ${TRIGGERNAME}"
./PlotEff/ploteff "${OUTPUTPATH}/output.root" "${OUTPUTPATH}" ${PTRANGE}