
#ifndef HELPERS
#define HELPERS

#include"TLorentzVector.h"

#include"../OniaIO/Data.h"

const float dRthreshold = 0.3f;
const float dPtThreshold = 0.3f;

bool isMatched(const TLorentzVector* recoMuon, const HltobjInput* onMuons);
bool isInAcceptance(float pt, float abseta);
bool isPassQualityCuts(const OniaInput* in, int index);

#endif