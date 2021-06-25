
#include"Readers.h"

HltObjReader::HltObjReader(TTree* input) : reader(input)
{
    reader.addInput("eta",&in.eta);
    reader.addInput("pt",&in.pt);
    reader.addInput("phi",&in.phi);
    reader.addInput("mass",&in.mass);
}

const HltobjInput* HltObjReader::readEntry(Long64_t entry)
{
    reader.readEntry(entry);
    return &in;
}

HltanalysisReader::HltanalysisReader(TTree* input) : reader(input)
{
    reader.addInput("Event",&in.event);
    reader.addInput("Run",&in.run);
    reader.buildIndex("Event");
}

const HltanalysisInput* HltanalysisReader::readEntry(Long64_t entry)
{
    reader.readEntry(entry);
    return &in;
}

OniaReader::OniaReader(TTree* input): reader(input)
{
    in.mom4 = new TClonesArray("TLorentzVector");
    reader.addInput("eventNb",&in.event);
    reader.addInput("SumET_HF",&in.sumhf);
    reader.addInput("Reco_mu_size", &in.size);
    reader.addInput("Reco_mu_nTrkWMea",&in.nTrkWMea);
    reader.addInput("Reco_mu_nPixWMea",&in.nPixWMea);
    reader.addInput("Reco_mu_dxy",&in.dxy);
    reader.addInput("Reco_mu_dz",&in.dz);
    reader.addInput("Reco_mu_4mom",&(in.mom4));
}

OniaReader::~OniaReader()
{
    delete in.mom4;
}

const OniaInput* OniaReader::readEntry(Long64_t entry)
{
    reader.readEntry(entry);
    return &in;
}