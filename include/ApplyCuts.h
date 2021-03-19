// Martin Duy Tat 25th February 2021
/**
 * ApplyCuts is a class that applies cuts to a TTree or TChain and outputs a TTree with the events that passed the selection
 * It is used as a functor after the cuts are specified in the constructor
 */

#ifndef APPLYCUTS
#define APPLYCUTS

#include"TCut.h"
#include"TTree.h"

class ApplyCuts {
  public:
    /**
     * Constructor that takes in a cut for the selection
     * @param Cuts Cuts that will be applied in selection
     */
    ApplyCuts(TCut Cuts, bool CopyDTFBranch = false);
    /**
     * () operator overload so that one can pass a TTree or TChain to this object and get a skimmed TTree back
     * @param TTree or TChain with event
     */
    TTree* operator()(TTree *InputTree) const;
  private:
    /**
     * Cuts that will be applied to selection
     */
    TCut m_Cuts;
    /**
     * If this flag is true, copy the branch Bu_constD0PV_M so that its type is Float_t, not an array of Float_t (RooFit doesn't work with arrays, very annoying)
     */
    bool m_CopyDTFBranch;
};

#endif
