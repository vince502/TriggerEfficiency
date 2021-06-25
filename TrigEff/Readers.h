#ifndef READERS
#define READERS

#include"../TreeReader/TreeReader.h"

#include"TClonesArray.h"

#include<vector>

struct HltobjInput
{
    std::vector<float> pt;
    std::vector<float> eta;
    std::vector<float> phi;
    std::vector<float> mass;
};

class HltObjReader
{
    TreeReader reader;
    HltobjInput in;

    public:
    HltObjReader(TTree* input);

    HltobjInput* readEntry(Long64_t entry);

};

struct HltanalysisInput
{
    Int_t event;
    Int_t run;
};

class HltanalysisReader
{
    TreeReader reader;
    HltanalysisInput in;

    public:
    HltanalysisReader(TTree* input);
    HltanalysisInput* readEntry(Long64_t entry);
};



struct OniaInput
{
    Int_t event;
    Float_t sumhf;
    Int_t size;
    Int_t nTrkWMea;
    Int_t nPixWMea;
    Float_t dxy;
    Float_t dz;
    std::unique_ptr<TClonesArray> mom4;
};

class OniaReader
{
    TreeReader reader;
    OniaInput in;

    public:
    OniaReader(TTree* input);

    OniaInput* readEntry(Long64_t entry);

};

#endif