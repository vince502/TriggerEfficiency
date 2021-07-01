
#include"PlotEff.h"
#include"TEfficiency.h"
#include"../OniaIO/OniaIO.h"
#include"../Utils/Utils.h"

#include<iostream>

void produceOutput(HistPair out, const std::string& outputpath);
void produceOutput(Hist2Pair out, const std::string& outputpath);
void readTotals(TFile* inputFile, Output* out);
void readPass(TFile* inputFile, Output* output);
Output allocateOutput();

void PlotEff(const char* inputfilename, const char* outputFilename)
{
    std::string outFilename=outputFilename;

    TFile* inputFile= OpenFile(inputfilename);
    if (inputFile==nullptr) return;

    Output output=allocateOutput();

    readTotals(inputFile,&output);
    readPass(inputFile,&output);

    produceOutput(output.y,outFilename);
    produceOutput(output.pt,outFilename);
    produceOutput(output.cent,outFilename);
    produceOutput(output.pt_fwd,outFilename);
    produceOutput(output.pt_mid,outFilename);
    produceOutput(output.pt_y,outFilename);
}

void readTotals(TFile* inputFile, Output* output)
{
    TTree* oniaTreeTotal= OpenTree(inputFile,"total");
    Reader<OniaOutput> onia(oniaTreeTotal);

    Long64_t entries= oniaTreeTotal->GetEntries();

    for(Long64_t i=0;i<entries;i++)
    {
        auto input= onia.readEntry(i);
        output->pt.den->Fill(input->pt);
        output->cent.den->Fill(input->cent);
        output->y.den->Fill(input->y);
        output->pt_y.den->Fill(input->y,input->pt);
        if (input->eta > endcapRap) 
            output->pt_fwd.den->Fill(input->pt);
        else
            output->pt_mid.den->Fill(input->pt);
    }
}

void readPass(TFile* inputFile, Output* output)
{
    TTree* oniaTreePass= OpenTree(inputFile,"pass");
    Reader<OniaOutput> onia(oniaTreePass);

    Long64_t entries= oniaTreePass->GetEntries();

    for(Long64_t i=0;i<entries;i++)
    {
        auto input= onia.readEntry(i);
        output->pt.num->Fill(input->pt);
        output->cent.num->Fill(input->cent);
        output->y.num->Fill(input->y);
        output->pt_y.num->Fill(input->y,input->pt);
        if (input->eta > endcapRap) 
            output->pt_fwd.num->Fill(input->pt);
        else
            output->pt_mid.num->Fill(input->pt);
    }
}

Output allocateOutput()
{
    Output out;
    out.pt.den= createTH1("den_pt", "denominator vs pt", &ptBins);
    out.pt.num= createTH1("num_pt", "numerator vs pt",&ptBins);
    out.pt.xlabel=histPtLabel;

    out.y.den = createTH1("den_y", "denominator vs y",&yBins);
    out.y.num = createTH1("num_y", "numerator vs y",&yBins);
    out.y.xlabel=histYLabel;

    out.cent.num= createTH1("num_cent","denominator vs centrality",&centBins);
    out.cent.den= createTH1("den_cent","numerator vs centrality",&centBins);
    out.cent.xlabel=histCentLabel;

    out.pt_fwd.den= createTH1("den_pt_fwd", "forward : denominator vs pt", &ptBins);
    out.pt_fwd.num= createTH1("num_pt_fwd", "forward : numerator vs pt",&ptBins);
    out.pt_fwd.xlabel=histPtLabel;

    out.pt_mid.den= createTH1("den_pt_mid", "mid barrel: denominator vs pt", &ptBins);
    out.pt_mid.num= createTH1("num_pt_mid", "mid barrel: numerator vs pt",&ptBins);
    out.pt_mid.xlabel=histPtLabel;

    out.pt_y.den =createTH2("den_pt_y", "denominator vs pt,y",&yBins,&ptBins);
    out.pt_y.num=createTH2("num_pt_y","numerator vs pt,y",&yBins,&ptBins);
    out.pt_y.xlabel=histYLabel;
    out.pt_y.ylabel=histPtLabel;

    return out;
}

void produceOutput(HistPair out, const std::string& outputpath)
{
    TEfficiency eff(*out.num,*out.den);
    const std::string eff_name="eff_"+std::string(out.num->GetName()).substr(4);
    eff.SetName(eff_name.data());

    const std::string outputfilename=outputpath+"/output";
    const char* ylabel= "";

    writeToCanvas(out.num,out.xlabel,ylabel,outputfilename);
    writeToCanvas(out.den,out.xlabel,ylabel,outputfilename);
    writeToCanvas(&eff,out.xlabel,"Efficiency",outputfilename);
}

void produceOutput(Hist2Pair out, const std::string& outputpath)
{
    TEfficiency eff(*out.num,*out.den);
    const std::string eff_name="eff_"+std::string(out.num->GetName()).substr(4);
    eff.SetName(eff_name.data());

    const std::string outputfilename=outputpath+"/output";

    const char* ylabel= out.ylabel ;

    writeToCanvas(out.num,out.xlabel,ylabel,outputfilename);
    writeToCanvas(out.den,out.xlabel,ylabel,outputfilename);
    writeToCanvas2D(&eff,out.xlabel,out.ylabel,outputfilename);
}

#if !defined(__CLING__)

int main(int argc, char **argv)
{
    if (argc==3)
        PlotEff(argv[1],argv[2]);
    else
        std::cerr << "Wrong number of parameters:\nUsage:\ninput , output\n";
    return 0;
}

#endif