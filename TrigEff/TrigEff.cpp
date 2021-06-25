
#include"TrigEff.h"
#include"Utils.h"
#include"Readers.h"

#include<iostream>

#include"TFile.h"

using std::cout;
using std::cerr;

void Process(TTree* oniaTree, TTree* hltobjectTree, TTree* hltanalysisTree);

const char oniaTreeName[]="hionia/myTree";
const char hltanalysisTreeName[] = "hltbitanalysis/HltTree";
const char hltobjDirectoryName[] = "hltobject/";

void TrigEff(const char* oniaFilename, const char* triggerFilename, const char* triggerName)
{
    TFile* oniaFile = OpenFile(oniaFilename);
    if (oniaFile==nullptr) return;
    
    TFile* triggerFile = OpenFile(triggerFilename);
    if (triggerFile==nullptr) return;

    TTree* oniaTree =OpenTree(oniaFile,oniaTreeName);
    TTree* hltanalysisTree=OpenTree(triggerFile,hltanalysisTreeName);

    std::string triggerPath=std::string(hltobjDirectoryName)+triggerName;
    TTree* hltobjectTree=OpenTree(triggerFile,triggerPath.data());

    if ((oniaTree==nullptr) || (hltanalysisTreeName==nullptr) || (hltobjectTree==nullptr))
        return;

    Process(oniaTree,hltobjectTree,hltanalysisTree);

    cout << "Success.\n";
}

void Process(TTree* oniaTree, TTree* hltobjectTree, TTree* hltanalysisTree)
{
    OniaReader onia(oniaTree);
    HltObjReader hltObj(hltobjectTree);
    HltanalysisReader hltAn(hltanalysisTree);

    Long64_t oniaEntryNum= oniaTree->GetEntries();

    for(Long64_t i=0;i< oniaEntryNum;i++)
    {
        if ((i % 100)==0) cout << "processing entries :" << i << " / " << oniaEntryNum << '\n';

        auto oniaInput = onia.readEntry(i);
        
        const Long64_t hltAnIndex=hltAn.findEntryByIndex(oniaInput->event);
        if (hltAnIndex<0) continue;

        auto analysisInput = hltAn.readEntry(hltAnIndex);
        auto hltobjInput = hltObj.readEntry(hltAnIndex);

        assert(oniaInput->event == analysisInput->event);

    }

    cout << "finished processing "<< oniaEntryNum << " entries\n";
}

#if !defined(__CLING__)

int main(int argc, char **argv)
{
    if (argc==4)
        TrigEff(argv[1],argv[2],argv[3]);
    else
        cerr << "Wrong number of parameters:\nUsage:\nOniaFilename , TriggerFilename, TriggerName\n";
    return 0;
}

#endif