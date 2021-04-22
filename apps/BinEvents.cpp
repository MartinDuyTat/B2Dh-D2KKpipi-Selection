// Martin Duy Tat 22nd April 2021
/**
 * BinEvents is an application that determines the bin number for each event and saves it to the ROOT file
 * @param 1 Name of ROOT file with B events
 * @param 2 Name of TTree
 * @param 3 Number of bins
 */

#include<iostream>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include"TBranch.h"
#include"TFile.h"
#include"TTree.h"
#include"Event.h"
#include"AmplitudePhaseSpace.h"

int main(int argc, char *argv[]) {
  if(argc != 4) {
    std::cout << "Need 3 input arguments\n";
    return 0;
  }
  std::cout << "Loading ROOT input file...\n";
  TFile Infile(argv[1], "UPDATE");
  TTree *Tree = nullptr;
  Infile.GetObject(argv[2], Tree);
  std::vector<Float_t> DaughterMomenta(16);
  Tree->SetBranchAddress("Bu_constD0PV_D0_Kplus_PX", DaughterMomenta.data() + 0);
  Tree->SetBranchAddress("Bu_constD0PV_D0_Kplus_PY", DaughterMomenta.data() + 1);
  Tree->SetBranchAddress("Bu_constD0PV_D0_Kplus_PZ", DaughterMomenta.data() + 2);
  Tree->SetBranchAddress("Bu_constD0PV_D0_Kplus_PE", DaughterMomenta.data() + 3);
  Tree->SetBranchAddress("Bu_constD0PV_D0_Kplus_0_PX", DaughterMomenta.data() + 4);
  Tree->SetBranchAddress("Bu_constD0PV_D0_Kplus_0_PY", DaughterMomenta.data() + 5);
  Tree->SetBranchAddress("Bu_constD0PV_D0_Kplus_0_PZ", DaughterMomenta.data() + 6);
  Tree->SetBranchAddress("Bu_constD0PV_D0_Kplus_0_PE", DaughterMomenta.data() + 7);
  Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_PX", DaughterMomenta.data() + 8);
  Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_PY", DaughterMomenta.data() + 9);
  Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_PZ", DaughterMomenta.data() + 10);
  Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_PE", DaughterMomenta.data() + 11);
  Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PX", DaughterMomenta.data() + 12);
  Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PY", DaughterMomenta.data() + 13);
  Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PZ", DaughterMomenta.data() + 14);
  Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PE", DaughterMomenta.data() + 15);
  int BinNumber;
  TBranch *Branch = Tree->Branch("BinNumber", &BinNumber, "BinNumber/I");
  std::cout << "Input event ready\n";
  AmplitudePhaseSpace aph(std::atoi(argv[3]));
  std::cout << "Binning events...\n";
  for(int i = 0; i < Tree->GetEntries(); i++) {
    Tree->GetEntry(i);
    std::vector<double> P(DaughterMomenta.begin(), DaughterMomenta.end());
    std::transform(P.begin(), P.end(), P.begin(), [](double &p) {return p/1000.0;});
    BinNumber = aph.WhichBin(Event(P));
    Branch->Fill();
  }
  Tree->Write();
  Infile.Close();
  std::cout << "Events are placed in their respective bins\n";
  return 0;
}
