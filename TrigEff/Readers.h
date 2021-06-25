#ifndef READERS
#define READERS

#include"../TreeReader/TreeReader.h"

#include"TClonesArray.h"

#include<vector>

const int maxArraySize=100;

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

    const HltobjInput* readEntry(Long64_t entry);

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
    const HltanalysisInput* readEntry(Long64_t entry);
    Long64_t findEntryByIndex(Long64_t index) {return reader.findEntryByIndex(index);}
};

struct OniaInput
{
    Int_t event;
    Float_t sumhf;
    Int_t size;
    Int_t nTrkWMea[maxArraySize];
    Int_t nPixWMea[maxArraySize];
    Float_t dxy[maxArraySize];
    Float_t dz[maxArraySize];
    TClonesArray* mom4;
};

class OniaReader
{
    TreeReader reader;
    OniaInput in;

    public:
    OniaReader(TTree* input);
    ~OniaReader();

    const OniaInput* readEntry(Long64_t entry);

};

#endif