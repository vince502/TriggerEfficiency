#ifndef UTILS
#define UTILS

#include"TFile.h"
#include"TTree.h"

TFile* OpenFile(const std::string& filename);
TFile* CreateFile(const std::string& filename);
TTree* OpenTree(TFile* file ,const std::string& treeName);

#endif