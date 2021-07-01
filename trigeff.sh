
#path to onia file
ONIAFILEPATH="../rootfiles/datasets/Run3Pre_dilepton/Oniatree_MC_miniAOD_PG_Pt_0p5_3_5p02TeV_cmssw11_2_2_Run3Cond_merged.root"
#path to trigger file
TRIGGERFILEPATH="../rootfiles/datasets/Run3Prep_DileptonHLT_2021/openHLT_Run3HLT_Dilepton_MC_Pt_0p5_100.root"
#name of the trigger inside trigger file
TRIGGERS=$( cat triggers.txt )
#path to directory to place output
OUTPUTPATH="../rootfiles/analysis/triggerStudy"

MAXJOBS=7

mkdir -p ${OUTPUTPATH}

echo "Trigger efficiency study"

#do the fits
if [ 1 = 1 ]
then
    echo "processing..."
    
    echo "reading reco file '${ONIAFILEPATH}'"
    echo "reading hltobj file '${TRIGGERFILEPATH}'"
    echo "output to:"
    echo "  ${OUTPUTPATH}/$( basename $ONIAFILEPATH)"
    #do the fitting jobs
    for TRIGGERNAME in $TRIGGERS
    do
        OUTPATH="${OUTPUTPATH}/$( basename $ONIAFILEPATH)/${TRIGGERNAME}"
        mkdir -p $OUTPATH
        echo "processing ${TRIGGERNAME}"
        ./TrigEff/trigeff ${ONIAFILEPATH} ${TRIGGERFILEPATH} ${TRIGGERNAME} $OUTPATH &> "${OUTPATH}/output.log"  &
        JOBS=( $(jobs -p) )
        JOBNUM="${#JOBS[@]}"
        if [ $MAXJOBS = $JOBNUM ]
        then
            wait -n
        fi
    done
    wait
    echo "all done"
fi

wait

for TRIGGERNAME in $TRIGGERS
do
echo "generating plots for ${TRIGGERNAME}"
OUTPATH="${OUTPUTPATH}/$( basename $ONIAFILEPATH)/${TRIGGERNAME}"
./PlotEff/ploteff "${OUTPATH}/output.root" "${OUTPATH}"
done