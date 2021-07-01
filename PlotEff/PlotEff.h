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

const std::vector<double> ptBins { 0.0, 0.5,1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0,6.5,7.0 };
const std::vector<double> yBins { -2.4, -2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.4 };
const std::vector<double> centBins { 190.0,191.0,192.0,193.0,194.0,195.0,196.0,197.0,198.0,199.0,200.0};

const char histPtLabel[]="p_{t}^{#mu#mu}(GeV/c)";
const char histYLabel[]="y^{#mu#mu}";
const char histCentLabel[]="Centrality";

const float endcapRap=1.6f;

#endif