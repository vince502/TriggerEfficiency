
#include"TrigEff.h"
#include"Utils.h"
#include"Readers.h"
#include"Helpers.h"

#include<iostream>

#include"TFile.h"

using std::cout;
using std::cerr;

Output Process(TTree* oniaTree, TTree* hltobjectTree, TTree* hltanalysisTree);

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

    //access trees

    TTree* oniaTree =OpenTree(oniaFile,oniaTreeName);
    TTree* hltanalysisTree=OpenTree(triggerFile,hltanalysisTreeName);

    std::string triggerPath=std::string(hltobjDirectoryName)+triggerName;
    TTree* hltobjectTree=OpenTree(triggerFile,triggerPath.data());

    if ((oniaTree==nullptr) || (hltanalysisTreeName==nullptr) || (hltobjectTree==nullptr))
        return;

    Output out= Process(oniaTree,hltobjectTree,hltanalysisTree);
    out.num_y->Write();
    out.num_pt->Write();
    out.den_y->Write();
    out.den_pt->Write();

    cout << "Success.\n";
}

Output Process(TTree* oniaTree, TTree* hltobjectTree, TTree* hltanalysisTree)
{
    OniaReader onia(oniaTree);
    HltObjReader hltObj(hltobjectTree);
    HltanalysisReader hltAn(hltanalysisTree);
    Output output=allocateOutput();

    Long64_t oniaEntryNum= oniaTree->GetEntries();

    for(Long64_t i=0;i< oniaEntryNum;i++)
    {
        if ((i % 10000)==0) cout << "processing entries :" << i << " / " << oniaEntryNum << '\n';

        auto oniaInput = onia.readEntry(i);
        
        for(int i=0;i<oniaInput->reco_QQ_size;i++)
        {
            int mupl_idx = oniaInput->reco_QQ_mupl_idx[i];
            int mumi_idx = oniaInput->reco_QQ_mumi_idx[i];

            if ((mupl_idx <0) || (mumi_idx <0) ) continue;
            const TLorentzVector* mupl= (TLorentzVector*) oniaInput->reco_mu_mom4->At(mupl_idx);
            if ((mupl==nullptr) || (!isInAcceptance(mupl))) continue;
            const TLorentzVector* mumi= (TLorentzVector*) oniaInput->reco_mu_mom4->At(mumi_idx);
            if ((mumi==nullptr) || (!isInAcceptance(mumi))) continue;

            if (!isPassQualityCuts(oniaInput,i)) continue;

            const TLorentzVector* onia= (TLorentzVector*) oniaInput->reco_QQ_mom4->At(i);
            float pt= onia->Pt();
            float y= onia->Rapidity();

            output.den_pt->Fill(pt);
            output.den_y->Fill(y);

            const Long64_t hltAnIndex=hltAn.findEntryByIndex(oniaInput->event);
            if (hltAnIndex<0) continue;

            auto analysisInput = hltAn.readEntry(hltAnIndex);
            auto hltobjInput = hltObj.readEntry(hltAnIndex);

            assert(oniaInput->event == analysisInput->event);

            if (isMatched(mupl,hltobjInput) && isMatched(mumi,hltobjInput))
            {
                output.num_pt->Fill(pt);
                output.num_y->Fill(y);
            }
        }

    }

    cout << "finished processing "<< oniaEntryNum << " entries\n";

    return output;
}

Output allocateOutput()
{
    Output out;
    out.den_pt= new TH1F("den_pt", histogramPtTitle, ptBins.size()-1, ptBins.data());
    out.den_pt->Sumw2();
    out.den_y = new TH1F("den_y", histogramYTitle,yBins.size()-1, yBins.data());
    out.den_y->Sumw2();
    out.num_pt= new TH1F("num_pt",histogramPtTitle,ptBins.size()-1,ptBins.data());
    out.num_pt->Sumw2();
    out.num_y = new TH1F("num_y", histogramYTitle,yBins.size(),yBins.data());
    out.num_y->Sumw2();

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