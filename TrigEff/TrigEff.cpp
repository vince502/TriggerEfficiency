
#include"TrigEff.h"
#include"Utils.h"
#include"Readers.h"
#include"Writers.h"
#include"Helpers.h"

#include<iostream>

#include"TFile.h"
#include"TEfficiency.h"

using std::cout;
using std::cerr;

void Process(Input* input, Output* output);

Output allocateOutput();
void produceOutput(HistPair out, const std::string& outputpath);

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

    //produceOutput(out.y,outFilename);
    //produceOutput(out.pt,outFilename);
    //produceOutput(out.cent,outFilename);
    //produceOutput(out.pt_fwd,outFilename);
    //produceOutput(out.pt_mid,outFilename);

    cout << "Success.\n";
}

void Process(Input* input, Output* output)
{
    OniaReader onia(input->oniaTree);
    HltObjReader hltObj(input->hltobjectTree);
    HltanalysisReader hltAn(input->hltanalysisTree);

    OniaWriter total(output->total);
    OniaWriter pass(output->pass);
    
    Long64_t oniaEntryNum= input->oniaTree->GetEntries();
    Long64_t entryStep= oniaEntryNum/50;

    for(Long64_t i=0;i< oniaEntryNum;i++)
    {
        if ((i % entryStep)==0) cout << "processing entries : " << round((100.0f*i)/oniaEntryNum) << "% " << i << " / " << oniaEntryNum << '\n';

        auto oniaInput = onia.readEntry(i);
        
        for(int i=0;i<oniaInput->reco_QQ_size;i++)
        {
            const TLorentzVector* onia= (TLorentzVector*) oniaInput->reco_QQ_mom4->At(i);
            const float pt= onia->Pt();
            const float y= onia->Rapidity();
            const int cent= oniaInput->centrality;

            if (abs(y) >2.4) continue;

            int mupl_idx = oniaInput->reco_QQ_mupl_idx[i];
            int mumi_idx = oniaInput->reco_QQ_mumi_idx[i];

            if ((mupl_idx <0) || (mumi_idx <0) ) continue;
            const TLorentzVector* mupl= (TLorentzVector*) oniaInput->reco_mu_mom4->At(mupl_idx);
            if ((mupl==nullptr) || (!isInAcceptance(mupl))) continue;
            const TLorentzVector* mumi= (TLorentzVector*) oniaInput->reco_mu_mom4->At(mumi_idx);
            if ((mumi==nullptr) || (!isInAcceptance(mumi))) continue;

            if (!isPassQualityCuts(oniaInput,i)) continue;

            //Passed acceptance and quality cuts
            total.output.pt=pt;
            total.output.y=y;
            total.output.cent = cent;
            total.output.m= onia->M();
            total.output.eta=onia->Eta();
            total.writeEntry();

            output->pt.den->Fill(pt);
            output->y.den->Fill(y);
            output->cent.den->Fill(cent);

            bool isFwd=abs(y) > endcapRap;

            if (isFwd) 
                output->pt_fwd.den->Fill(pt);
            else
                output->pt_mid.den->Fill(pt);

            //read hltobj

            const Long64_t hltAnIndex=hltAn.findEntryByIndex(oniaInput->event);
            if (hltAnIndex<0) continue;

            auto analysisInput = hltAn.readEntry(hltAnIndex);
            auto hltobjInput = hltObj.readEntry(hltAnIndex);

            assert(oniaInput->event == analysisInput->event);

            if (isMatched(mupl,hltobjInput) && isMatched(mumi,hltobjInput))
            {
                output->pt.num->Fill(pt);
                output->y.num->Fill(y);
                output->cent.num->Fill(cent);
                if (isFwd)
                    output->pt_fwd.num->Fill(pt);
                else
                    output->pt_mid.num->Fill(pt);

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
    out.pt.den= new TH1F("den_pt", histogramPtTitle, ptBins.size()-1, ptBins.data());
    out.pt.den->Sumw2();
    out.pt.num= new TH1F("num_pt",histogramPtTitle,ptBins.size()-1,ptBins.data());
    out.pt.num->Sumw2();
    out.y.den = new TH1F("den_y", histogramYTitle,yBins.size()-1, yBins.data());
    out.y.den->Sumw2();
    out.y.num = new TH1F("num_y", histogramYTitle,yBins.size()-1,yBins.data());
    out.y.num->Sumw2();

    out.cent.num= new TH1F("num_cent",histogramCentTitle,200,0,200);
    out.cent.num->Sumw2();
    out.cent.den= new TH1F("den_cent",histogramCentTitle,200,0,200);
    out.cent.den->Sumw2();

    out.pt_fwd.den= new TH1F("den_pt_fwd", histogramPtTitle, ptBins.size()-1, ptBins.data());
    out.pt_fwd.den->Sumw2();
    out.pt_fwd.num= new TH1F("num_pt_fwd",histogramPtTitle,ptBins.size()-1,ptBins.data());
    out.pt_fwd.num->Sumw2();
    out.pt_mid.den= new TH1F("den_pt_mid", histogramPtTitle, ptBins.size()-1, ptBins.data());
    out.pt_mid.den->Sumw2();
    out.pt_mid.num= new TH1F("num_pt_mid",histogramPtTitle,ptBins.size()-1,ptBins.data());
    out.pt_mid.num->Sumw2();

    out.pass = new TTree("pass","passing dimuons");
    out.total = new TTree("total","total dimuons");

    return out;
}

void produceOutput(HistPair out, const std::string& outputpath)
{
    TEfficiency eff(*out.num,*out.den);
    const std::string num_outputfilename=outputpath+"/output_"+out.num->GetName()+".pdf";
    const std::string den_outputfilename=outputpath+"/output_"+out.den->GetName()+".pdf";
    const std::string eff_outputfilename=outputpath+"/output_eff_"+eff.GetName()+".pdf";

    out.num->Write();
    out.den->Write();
    eff.Write();

    out.num->SaveAs(num_outputfilename.data());
    out.den->SaveAs(den_outputfilename.data());
    eff.SaveAs(eff_outputfilename.data());
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