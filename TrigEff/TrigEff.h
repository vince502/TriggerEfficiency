
#include"RtypesCore.h"

#include<array>
#include"TH1.h"

struct Output
{
    TH1* den_pt;
    TH1* den_y;
    TH1* num_pt;
    TH1* num_y;
};

const char oniaTreeName[]="hionia/myTree";
const char hltanalysisTreeName[] = "hltbitanalysis/HltTree";
const char hltobjDirectoryName[] = "hltobject/";

const std::array<double,10> ptBins { 0.0, 0.5,1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5 };
const std::array<double,11> yBins { -2.4, -2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.4 };

const char histogramPtTitle[] = "Trigger Efficiency vs p_{t}^{#mu#mu}; p_{t}^{#mu#mu}(GeV/c); Efficiency";
const char histogramYTitle[] = "Trigger Efficiency vs y^{#mu#mu}; y^{#mu#mu}(GeV/c); Efficiency";