// Martin Duy Tat 22nd April 2021
/**
 * BinEvents is an application that determines the bin number for each event and saves it to the ROOT file
 * @param 1 Name of ROOT file with B events
 * @param 2 Name of TTree
 * @param 3 Name of ROOT output file
 * @param 4 Year of dataset
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
  if(argc != 5) {
    std::cout << "Need 4 input arguments\n";
    return 0;
  }
  std::cout << "Loading ROOT input file...\n";
  TFile Infile(argv[1], "READ");
  TTree *Tree = nullptr;
  Infile.GetObject(argv[2], Tree);
  std::cout << "Input file ready\n";
  std::cout << "Creating output ROOT file...\n";
  TFile Outfile(argv[3], "RECREATE");
  TTree *OutTree = Tree->CloneTree(0);
  int BinNumber_4Bins, BinNumber_6Bins, BinNumber_8Bins;
  OutTree->Branch("BinNumber_4Bins", &BinNumber_4Bins, "BinNumber_4Bins/I");
  OutTree->Branch("BinNumber_6Bins", &BinNumber_6Bins, "BinNumber_6Bins/I");
  OutTree->Branch("BinNumber_8Bins", &BinNumber_8Bins, "BinNumber_8Bins/I");
  std::cout << "Output ROOT file ready\n";
  std::cout << "Booking variables...\n";
  std::vector<Double_t> DaughterMomenta(16);
  std::vector<Double_t> DaughterIDs(4);
  Tree->SetBranchAddress("Bu_constD0PV_D0_Kplus_ID", DaughterIDs.data() + 0);
  Tree->SetBranchAddress("Bu_constD0PV_D0_Kplus_0_ID", DaughterIDs.data() + 1);
  Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_ID", DaughterIDs.data() + 2);
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
  if(std::stoi(argv[4]) == 2011 || std::stoi(argv[4]) == 2012) {
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_0_ID", DaughterIDs.data() + 3);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_0_PX", DaughterMomenta.data() + 12);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_0_PY", DaughterMomenta.data() + 13);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_0_PZ", DaughterMomenta.data() + 14);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_0_PE", DaughterMomenta.data() + 15);
  } else {
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_ID", DaughterIDs.data() + 3);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PX", DaughterMomenta.data() + 12);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PY", DaughterMomenta.data() + 13);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PZ", DaughterMomenta.data() + 14);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PE", DaughterMomenta.data() + 15);
  }
  std::cout << "Variables ready\n";
  std::cout << "Preparing binning scheme...\n";
  AmplitudePhaseSpace aph4(4), aph6(6), aph8(8);
  aph4.SetBinEdges(std::vector<double>{1.20923});
  aph6.SetBinEdges(std::vector<double>{0.645101, 1.72065});
  aph8.SetBinEdges(std::vector<double>{0.458065, 1.15464, 2.09644});
  aph4.UseVariableBinWidths(true);
  aph6.UseVariableBinWidths(true);
  aph8.UseVariableBinWidths(true);
  std::cout << "Ready to bin events\n";
  std::cout << "Binning events...\n";
  for(int i = 0; i < Tree->GetEntries(); i++) {
    Tree->GetEntry(i);
    if(std::stoi(argv[4]) == 2011 || std::stoi(argv[4]) == 2012) {
      int KPlusIndex = std::find(DaughterIDs.begin(), DaughterIDs.end(), 321) - DaughterIDs.begin();
      if(KPlusIndex != 0) {
	std::swap(DaughterIDs[0], DaughterIDs[KPlusIndex]);
	std::swap_ranges(DaughterMomenta.begin() + 0, DaughterMomenta.begin() + 4, DaughterMomenta.begin() + 4*KPlusIndex);
      }
      int KMinusIndex = std::find(DaughterIDs.begin(), DaughterIDs.end(), -321) - DaughterIDs.begin();
      if(KMinusIndex != 0) {
	std::swap(DaughterIDs[1], DaughterIDs[KMinusIndex]);
	std::swap_ranges(DaughterMomenta.begin() + 4, DaughterMomenta.begin() + 8, DaughterMomenta.begin() + 4*KMinusIndex);
      }
      int piPlusIndex = std::find(DaughterIDs.begin(), DaughterIDs.end(), 211) - DaughterIDs.begin();
      if(piPlusIndex != 0) {
	std::swap(DaughterIDs[2], DaughterIDs[piPlusIndex]);
	std::swap_ranges(DaughterMomenta.begin() + 8, DaughterMomenta.begin() + 12, DaughterMomenta.begin() + 4*piPlusIndex);
      }
      int piMinusIndex = std::find(DaughterIDs.begin(), DaughterIDs.end(), -211) - DaughterIDs.begin();
      if(piMinusIndex != 0) {
	std::swap(DaughterIDs[3], DaughterIDs[piMinusIndex]);
	std::swap_ranges(DaughterMomenta.begin() + 12, DaughterMomenta.begin() + 16, DaughterMomenta.begin() + 4*piMinusIndex);
      }
    }
    std::vector<double> P(DaughterMomenta.begin(), DaughterMomenta.end());
    std::transform(P.begin(), P.end(), P.begin(), [](double &p) {return p/1000.0;});
    BinNumber_4Bins = aph4.WhichBin(Event(P));
    BinNumber_6Bins = aph6.WhichBin(Event(P));
    BinNumber_8Bins = aph8.WhichBin(Event(P));
    OutTree->Fill();
  }
  OutTree->Write();
  Outfile.Close();
  Infile.Close();
  std::cout << "Events are placed in their respective bins\n";
  return 0;
}
