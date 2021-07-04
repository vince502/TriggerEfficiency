#ifndef PLOTEFF
#define PLOTEFF

#include"TH1.h"
#include"TH2.h"

struct HistPair
{
    TH1* num;
    TH1* den;
    const char* xlabel;
};

struct Hist2Pair
{
    TH2* num;
    TH2* den;
    const char* xlabel;
    const char* ylabel;
};

struct Output
{
    HistPair pt;
    HistPair y;
    HistPair pt_mid;
    HistPair pt_fwd;
    HistPair cent;
    Hist2Pair pt_y;
};

const std::vector<double> ptBinsLow=[]()
{
    std::vector<double> out;
    for(int i=0;i<(4*2);i++) out.push_back(i*0.5);
    return out;
}();
const std::vector<double> ptBinsHigh=[]()
{
    std::vector<double> out;
    for(int i=3;i<100;i+=5) out.push_back(i);
    return out;
}();
const std::vector<double> yBins { -2.4, -2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.4 };
const std::vector<double> centBins { 194.0,195.0,196.0,197.0,198.0,199.0,200.0};

const char histPtLabel[]="p_{t}^{#mu#mu}(GeV/c)";
const char histYLabel[]="y^{#mu#mu}";
const char histCentLabel[]="Centrality";

const float endcapRap=1.6f;

#endif