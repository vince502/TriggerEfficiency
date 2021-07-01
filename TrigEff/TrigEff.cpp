
#include"../OniaIO/OniaIO.h"
#include"../Utils/Utils.h"
#include"TrigEff.h"
#include"Helpers.h"

#include<iostream>

#include"TFile.h"
#include"TEfficiency.h"

using std::cout;
using std::cerr;

void Process(Input* input, Output* output);

Output allocateOutput();

void TrigEff(const char* oniaFilename, const char* triggerFilename, const char* triggerName, const char* outputFilename)
{
    //open and create required files
    TFile* oniaFile = OpenFile(oniaFilename);
    if (oniaFile==nullptr) return;
    
    TFile* triggerFile = OpenFile(triggerFilename);
    if (triggerFile==nullptr) return;

    std::string outFilename=outputFilename;

    TFile* outputFile = CreateFile(outFilename+"/output.root");

    //init inputs
    Input input;

    input.oniaTree =OpenTree(oniaFile,oniaTreeName);
    input.hltanalysisTree=OpenTree(triggerFile,hltanalysisTreeName);

    std::string triggerPath=std::string(hltobjDirectoryName)+triggerName;
    input.hltobjectTree=OpenTree(triggerFile,triggerPath.data());

    if ((input.oniaTree==nullptr) || (input.hltanalysisTree==nullptr) || (input.hltobjectTree==nullptr))
        return;

    //init outputs
    Output output=allocateOutput();

    Process(&input,&output);

    output.pass->Write();
    output.total->Write();

    cout << "Success.\n";
}

void Process(Input* input, Output* output)
{
    Reader<OniaInput> onia(input->oniaTree);
    Reader<HltobjInput> hltObj(input->hltobjectTree);
    Reader<HltanalysisInput> hltAn(input->hltanalysisTree);

    hltAn.buildIndex("Event");
    Writer<OniaOutput> total(output->total);
    Writer<OniaOutput> pass(output->pass);
    
    Long64_t oniaEntryNum= input->oniaTree->GetEntries();
    Long64_t entryStep= oniaEntryNum/50;

    for(Long64_t i=0;i< oniaEntryNum;i++)
    {
        if ((i % entryStep)==0) cout << "processing entries : " << round((100.0f*i)/oniaEntryNum) << "% " << i << " / " << oniaEntryNum << '\n';

        const OniaInput* oniaInput = onia.readEntry(i);
        
        for(int i=0;i<oniaInput->reco_mu_size;i++)
        {
            const TLorentzVector* mu= (TLorentzVector*) oniaInput->reco_mu_mom4->At(i);
            const float pt= mu->Pt();
            const float y= mu->Rapidity();
            const float eta= mu->Eta();
            const int cent= oniaInput->centrality;

            if (!isInAcceptance(pt,abs(eta))) continue;

            if (!isPassQualityCuts(oniaInput,i)) continue;

            //Passed acceptance and quality cuts
            total.output.pt=pt;
            total.output.y=y;
            total.output.cent = cent;
            total.output.m= mu->M();
            total.output.eta=eta;
            total.writeEntry();

            //read hltobj

            const Long64_t hltAnIndex=hltAn.findEntryByIndex(oniaInput->event);
            if (hltAnIndex<0) continue;

            const HltanalysisInput* analysisInput = hltAn.readEntry(hltAnIndex);
            const HltobjInput* hltobjInput = hltObj.readEntry(hltAnIndex);

            assert(oniaInput->event == analysisInput->event);

            if (isMatched(mu,hltobjInput))
            {
                pass.output= total.output;
                pass.writeEntry();
            }
        }
    }

    cout << "finished processing "<< oniaEntryNum << " entries\n";
}

Output allocateOutput()
{
    Output out;

    out.pass = new TTree("pass","passing dimuons");
    out.total = new TTree("total","total dimuons");

    return out;
}

#if !defined(__CLING__)

int main(int argc, char **argv)
{
    if (argc==5)
        TrigEff(argv[1],argv[2],argv[3],argv[4]);
    else
        cerr << "Wrong number of parameters:\nUsage:\nOnia Filename , Trigger Filename, Trigger Name, OutputFilename\n";
    return 0;
}

#endif