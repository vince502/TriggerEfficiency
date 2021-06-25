
#include"Utils.h"

#include<iostream>

TFile* OpenFile(const char* filename)
{
    std::cout << "opening root file: " << filename << '\n';
    TFile* file = TFile::Open(filename, "READ");
    //input file is found? is output filename valid?
    if (file==nullptr) 
        std::cout << std::string("file ") + filename +" cannot be read\n";
    return file;
}

TTree* OpenTree(TFile* file ,const char* treeName)
{
    std::cout << "reading tree '" << treeName << "' from file '" << file->GetName() << "'\n";
    TTree* tree =nullptr;
    file->GetObject(treeName,tree);
    if (tree==nullptr)
    {
        std::cerr << "Tree '" << treeName << "' does not exist.\n";
    }
    return tree;
}