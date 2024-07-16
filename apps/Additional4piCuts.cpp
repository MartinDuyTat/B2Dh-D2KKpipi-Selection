// Martin Duy Tat 28th May 2024
/**
 * Additional4piCuts adds some additional cuts on the 4pi mode
 * This is to merge the Oxford and Bristol analyses
 * @param 1 ROOT filename with data sample
 * @param 2 Filename of output ROOT file
 */

#include<iostream>
#include<string>
#include<vector>
#include"TChain.h"
#include"TEntryList.h"
#include"TFile.h"

std::string GetCuts();

int main(int argc, char *argv[]) {
  if(argc != 3) {
    std::cout << "Please input 2 arguments\n";
  }
  std::cout << "Applying additional 4pi cuts...\n";
  TChain Chain("DecayTree");
  Chain.Add(argv[1]);
  Chain.Draw(">> elist", GetCuts().c_str(), "entrylist");
  TEntryList *elist = (TEntryList*)gDirectory->Get("elist");
  Chain.SetEntryList(elist);
  TFile File(argv[2], "RECREATE");
  TTree *OutputTree = Chain.CloneTree(0);
  for(Long64_t i = 0; i < elist->GetN(); i++) {
    Chain.GetEntry(Chain.GetEntryNumber(i));
    OutputTree->Fill();
  }
  OutputTree->Write();
  File.Close();
  std::cout << "4pi tuple ready\n";
  return 0;
}

std::string GetCuts() {
  std::vector<std::string> Cuts;
  Cuts.push_back("h1_PT < 35000");
  Cuts.push_back("h2_PT < 35000");
  Cuts.push_back("h3_PT < 35000");
  Cuts.push_back("h4_PT < 35000");
  Cuts.push_back("Bach_PT < 70000");
  Cuts.push_back("h1_ProbNNpi > 0.02");
  Cuts.push_back("h2_ProbNNpi > 0.02");
  Cuts.push_back("h3_ProbNNpi > 0.02");
  Cuts.push_back("h4_ProbNNpi > 0.02");
  Cuts.push_back("h1_ProbNNk < 0.96");
  Cuts.push_back("h2_ProbNNk < 0.96");
  Cuts.push_back("h3_ProbNNk < 0.96");
  Cuts.push_back("h4_ProbNNk < 0.96");
  Cuts.push_back("D0_IPCHI2_OWNPV > 1.5");
  Cuts.push_back("D0_FDCHI2_OWNPV > 50.0");
  Cuts.push_back("Bach_IPCHI2_OWNPV > 5.0");
  Cuts.push_back("Bu_IPCHI2_OWNPV < 20.0");
  Cuts.push_back("Bu_FDCHI2_OWNPV > 30.0");
  Cuts.push_back("Bu_DIRA_OWNPV > 0.9995");
  Cuts.push_back("Bach_ETA > 1.5");
  Cuts.push_back("Bach_ETA < 5.0");
  Cuts.push_back("nTracks > 0");
  Cuts.push_back("nTracks < 500");
  Cuts.push_back("h1_ProbNNpi*(1 - h1_ProbNNk) > 0.05");
  Cuts.push_back("h2_ProbNNpi*(1 - h2_ProbNNk) > 0.05");
  Cuts.push_back("h3_ProbNNpi*(1 - h3_ProbNNk) > 0.05");
  Cuts.push_back("h4_ProbNNpi*(1 - h4_ProbNNk) > 0.05");
  std::string AllCuts;
  for(const auto &Cut : Cuts) {
    if(Cut != Cuts[0]) {
      AllCuts += " && ";
    }
    AllCuts += "(" + Cut + ")";
  }
  return AllCuts;
}
