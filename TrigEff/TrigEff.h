
#include"RtypesCore.h"

#include<array>
#include"TH1.h"
#include"TTree.h"

struct HistPair
{
    TH1* num;
    TH1* den;
};

struct Output
{
    HistPair pt;
    HistPair y;
    HistPair pt_mid;
    HistPair pt_fwd;
    HistPair cent;
    TTree* total;
    TTree* pass;
};

struct Input
{
    TTree* oniaTree;
    TTree* hltanalysisTree;
    TTree* hltobjectTree;
};

const char oniaTreeName[]="hionia/myTree";
const char hltanalysisTreeName[] = "hltbitanalysis/HltTree";
const char hltobjDirectoryName[] = "hltobject/";

//const std::array<double,10> ptBins { 0.0, 0.5,1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5 };
const std::array<double,16> ptBins { 0.0, 0.2,0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0,2.2,2.4,2.6,2.8,3.0 };
const std::array<double,11> yBins { -2.4, -2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.4 };

const char histogramPtTitle[] = "Trigger Efficiency vs p_{t}^{#mu#mu}; p_{t}^{#mu#mu}(GeV/c); Efficiency";
const char histogramYTitle[] = "Trigger Efficiency vs y^{#mu#mu}; y^{#mu#mu}(GeV/c); Efficiency";
const char histogramCentTitle[] = "Trigger Efficiency vs Centrality; Centrality; Efficiency";

const float endcapRap=1.6f;