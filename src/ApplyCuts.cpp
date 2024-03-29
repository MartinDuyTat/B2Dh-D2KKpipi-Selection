// Martin Duy Tat 25th February 2021

#include"ApplyCuts.h"
#include"TCut.h"
#include"TTree.h"
#include"TEntryList.h"
#include"TDirectory.h"
#include"TRandom.h"

ApplyCuts::ApplyCuts(TCut Cuts, bool CopyDTFBranch, double Smearing): m_Cuts(Cuts), m_CopyDTFBranch(CopyDTFBranch), m_Smearing(Smearing) {
}

TTree* ApplyCuts::operator()(TTree *InputTree) const {
  InputTree->Draw(">> elist", m_Cuts, "entrylist");
  TEntryList *elist = (TEntryList*)gDirectory->Get("elist");
  InputTree->SetEntryList(elist);
  if(m_CopyDTFBranch || m_Smearing != 0.0) {
    InputTree->SetBranchStatus("Bu_constD0PV_M", 0);
    InputTree->SetBranchStatus("Bu_constD0PV_swapBachToK_M", 0);
    InputTree->SetBranchStatus("Bu_constD0PV_swapBachToPi_M", 0);
  }
  TTree *OutputTree = InputTree->CloneTree(0);
  Float_t Bu_constD0PV_M, Bu_constD0PV_swapBachToK_M, Bu_constD0PV_swapBachToPi_M;
  if(m_CopyDTFBranch || m_Smearing != 0.0) {
    InputTree->SetBranchStatus("Bu_constD0PV_M", 1);
    InputTree->SetBranchAddress("Bu_constD0PV_M", &Bu_constD0PV_M);
    OutputTree->Branch("Bu_constD0PV_M", &Bu_constD0PV_M, "Bu_constD0PV_M/F");
    InputTree->SetBranchStatus("Bu_constD0PV_swapBachToK_M", 1);
    InputTree->SetBranchAddress("Bu_constD0PV_swapBachToK_M", &Bu_constD0PV_swapBachToK_M);
    OutputTree->Branch("Bu_constD0PV_swapBachToK_M", &Bu_constD0PV_swapBachToK_M, "Bu_constD0PV_swapBachToK_M/F");
    InputTree->SetBranchStatus("Bu_constD0PV_swapBachToPi_M", 1);
    InputTree->SetBranchAddress("Bu_constD0PV_swapBachToPi_M", &Bu_constD0PV_swapBachToPi_M);
    OutputTree->Branch("Bu_constD0PV_swapBachToPi_M", &Bu_constD0PV_swapBachToPi_M, "Bu_constD0PV_swapBachToPi_M/F");
  }
  for(Long64_t i = 0; i < elist->GetN(); i++) {
    InputTree->GetEntry(InputTree->GetEntryNumber(i));
    if(m_Smearing != 0.0) {
      Bu_constD0PV_M += gRandom->Gaus(0.0, m_Smearing);
      if(Bu_constD0PV_M < 5080.0 || Bu_constD0PV_M > 5800.0) {
	continue;
      }
    }
    OutputTree->Fill();
  }
  return OutputTree;
}
