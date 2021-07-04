
#path to reco file
ONIAFILEPATH="../rootfiles/datasets/Run3Pre_dilepton/Oniatree_MC_miniAOD_PG_Pt_0p5_3_5p02TeV_cmssw11_2_2_Run3Cond_merged.root"
#path to trigger file
TRIGGERFILEPATH="../rootfiles/datasets/Run3Prep_DileptonHLT_2021/openHLT_Run3HLT_Dilepton_MC_Pt_0p5_100.root"
#list of triggers to process, listed in file triggers.txt
TRIGGERS=$( cat triggers.txt )
#path to directory to place output
OUTPUTPATH="../rootfiles/analysis/triggerStudy"
#maximum number of cores/threads to use simultaneusly, one core/thread process one trigger
MAXJOBS=7

mkdir -p ${OUTPUTPATH}

echo "Full Trigger efficiency study"

#do the processing

echo "processing..."

echo "reading reco file '${ONIAFILEPATH}'"
echo "reading hltobj file '${TRIGGERFILEPATH}'"
echo "output to:"
echo "  ${OUTPUTPATH}/$( basename $ONIAFILEPATH)"

for TRIGGERNAME in $TRIGGERS
do
    OUTPATH="${OUTPUTPATH}/$( basename ${ONIAFILEPATH%.*})/${TRIGGERNAME}"
    mkdir -p $OUTPATH
    echo "processing ${TRIGGERNAME}"
    ./trigeff.sh ${ONIAFILEPATH} ${TRIGGERFILEPATH} ${TRIGGERNAME} $OUTPATH &> "${OUTPATH}/output.log"  &
    JOBS=( $(jobs -p) )
    JOBNUM="${#JOBS[@]}"
    if [ $MAXJOBS = $JOBNUM ]
    then
        wait -n
    fi
done
wait
echo "all done"