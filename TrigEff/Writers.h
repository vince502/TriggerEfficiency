#ifndef WRITERS
#define WRITERS

#include"../TreeIO/TreeWriter.h"

struct OniaOutput
{
    Float_t pt;
    Float_t m;
    Float_t y;
    Float_t eta;
    Float_t cent;
};


class OniaWriter
{
    TreeWriter writer;

    public:
    OniaWriter(TTree* treeInput);

    void writeEntry() { writer.writeEntry();}

    OniaOutput output;

};

#endif