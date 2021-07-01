
#include"Helpers.h"

bool isMatched(const TLorentzVector* recoMuon, const HltobjInput* onMuons)
{
    int onlineMuonSize= onMuons->eta->size();
    for (int i=0;i<onlineMuonSize;i++)
    {
        float deltaEta= recoMuon->Eta() - onMuons->eta->at(i);
        float deltaPhi= recoMuon->Phi() - onMuons->phi->at(i);
        if (sqrt(deltaEta*deltaEta+deltaPhi*deltaPhi) < dRthreshold)
        {
            float ptReco= recoMuon->Pt();
            if (abs(( onMuons->pt->at(i) - ptReco )/ptReco)) 
                return true;
        }
    }
    return false;
}

bool isInAcceptance(const TLorentzVector* muon)
{
    float abseta= abs(muon->Eta());
    float pt= muon->Pt();
    if (abseta > 2.4) return false;
    if (abseta < 1.2 ) return pt >3.5;
    if ((abseta >= 1.2) && (abseta < 2.1)) return pt >= 5.47-1.89*abseta;
    return pt >1.5;
}

bool isPassQualityCuts(const OniaInput* in, int index)
{
    if (in->reco_mu_nPixWMea[index] <=0 ) return false;
    if (in->reco_mu_nTrkWMea[index] <=5 ) return false;
    if (in->reco_mu_dxy[index] >=0.3 ) return false;
    return (in->reco_mu_dz[index] < 20.0);
}