
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
    in.reco_mu_mom4 = new TClonesArray("TLorentzVector");
    in.reco_QQ_mom4 = new TClonesArray("TLorentzVector");

    reader.addInput("eventNb",&in.event);
    reader.addInput("SumET_HF",&in.sumhf);

    reader.addInput("Reco_mu_size", &in.reco_mu_size);
    reader.addInput("Reco_mu_nTrkWMea",&in.reco_mu_nTrkWMea);
    reader.addInput("Reco_mu_nPixWMea",&in.reco_mu_nPixWMea);
    reader.addInput("Reco_mu_dxy",&in.reco_mu_dxy);
    reader.addInput("Reco_mu_dz",&in.reco_mu_dz);
    reader.addInput("Reco_mu_4mom",&(in.reco_mu_mom4));

    reader.addInput("Reco_QQ_size", &(in.reco_QQ_size));
    reader.addInput("Reco_QQ_4mom",&in.reco_QQ_mom4);
    reader.addInput("Reco_QQ_mumi_idx",&in.reco_QQ_mumi_idx);
    reader.addInput("Reco_QQ_mupl_idx",&in.reco_QQ_mupl_idx);
}

OniaReader::~OniaReader()
{
    delete in.reco_mu_mom4;
    delete in.reco_QQ_mom4;
}

const OniaInput* OniaReader::readEntry(Long64_t entry)
{
    reader.readEntry(entry);
    return &in;
}