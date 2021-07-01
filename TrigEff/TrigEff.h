
#include"RtypesCore.h"

#include<array>
#include"TH1.h"
#include"TTree.h"

struct Output
{
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

