#ifndef UTILS
#define UTILS

#include"TFile.h"
#include"TTree.h"

TFile* OpenFile(const char* filename);
TTree* OpenTree(TFile* file ,const char* treeName);

#endif