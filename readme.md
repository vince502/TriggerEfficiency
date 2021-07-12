## Muon Trigger Efficiency

# HOW TO USE
To use the code, first compile with with make command in the main directory:
```
make
```
this must be done each time C++ code is modified.

To run calculate the efficiency for all triggers, use the
multiTrigeff.sh bash script. Inside set the variables:
ONIAFILEPATH, TRIGGERFILEPATH, OUTPUTPATH, PTRANGE, MAXJOBS
to configure the path to reco file, trigger file and output directory respectively.
Also files: triggersL1.txt triggersL2.txt and triggersL3.txt contains the list of
triggers to process.

Then run with command:
```
./multiTrigeff.sh
```
inside main directory.
The code will calculate efficiencies for triggers provided in parallel,
up to MAXJOBS triggers simultaneusly and put it in OUTPUTPATH directory.
Output is placed inside OUTPUTPATH path inside a directory named after the reco file used.
inside that directory there is one directory named as each trigger, with the results inside each.
Efficiencies are calculated as a function of pt, rapidity, centrality. Also there is separated efficiencies calculated for mid barrel and forward region as a function of pt.
Also a plot superimposed efficiencies as function of pt per trigger level is output in this directory.

Similarly the file trigeff.sh can be configured and ran to calculate trigger efficiency of just one trigger
at a time.