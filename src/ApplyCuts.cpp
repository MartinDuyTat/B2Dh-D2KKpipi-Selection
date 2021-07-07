// Martin Duy Tat 25th February 2021

#include"ApplyCuts.h"
#include"TCut.h"
#include"TTree.h"
#include"TEntryList.h"
#include"TDirectory.h"

ApplyCuts::ApplyCuts(TCut Cuts, bool CopyDTFBranch): m_Cuts(Cuts), m_CopyDTFBranch(CopyDTFBranch) {
}

TTree* ApplyCuts::operator()(TTree *InputTree) const {
  InputTree->Draw(">> elist", m_Cuts, "entrylist");
  TEntryList *elist = (TEntryList*)gDirectory->Get("elist");
  InputTree->SetEntryList(elist);
  if(m_CopyDTFBranch) {
    InputTree->SetBranchStatus("Bu_constD0PV_M", 0);
  }
  TTree *OutputTree = InputTree->CloneTree(0);
  OutputTree->SetDirectory(0);
  Float_t Bu_constD0PV_M;
  if(m_CopyDTFBranch) {
    InputTree->SetBranchStatus("Bu_constD0PV_M", 1);
    InputTree->SetBranchAddress("Bu_constD0PV_M", &Bu_constD0PV_M);
    OutputTree->Branch("Bu_constD0PV_M", &Bu_constD0PV_M, "Bu_constD0PV_M/F");
  }
  for(Long64_t i = 0; i < elist->GetN(); i++) {
    InputTree->GetEntry(InputTree->GetEntryNumber(i));
    OutputTree->Fill();
  }
  return OutputTree;
}
