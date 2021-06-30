
#include"Utils.h"

#include<iostream>

TFile* OpenFile(const std::string& filename)
{
    std::cout << "opening root file: " << filename << '\n';
    TFile* file = TFile::Open(filename.data(), "READ");
    //input file is found? is output filename valid?
    if (file==nullptr) 
        std::cout << std::string("file ") + filename +" cannot be read\n";
    return file;
}

TFile* CreateFile(const std::string& filename)
{
    std::cout << "creating root file: " << filename << '\n';
    TFile* file = TFile::Open(filename.data(), "CREATE");
    //input file is found? is output filename valid?
    if (file==nullptr) 
        std::cout << std::string("file ") + filename +" cannot be created\n";
    return file;
}

TTree* OpenTree(TFile* file ,const std::string& treeName)
{
    std::cout << "reading tree '" << treeName << "' from file '" << file->GetName() << "'\n";
    TTree* tree =nullptr;
    file->GetObject(treeName.data(),tree);
    if (tree==nullptr)
    {
        std::cerr << "Tree '" << treeName << "' does not exist.\n";
    }
    return tree;
}