
#include"Writers.h"

OniaWriter::OniaWriter(TTree* treeInput) : writer(treeInput)
{
    writer.addOutput("pt",&output.pt);
    writer.addOutput("y",&output.y);
    writer.addOutput("cent",&output.cent);
    writer.addOutput("eta",&output.eta);
    writer.addOutput("m",&output.m);
}