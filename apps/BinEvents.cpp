// Martin Duy Tat 22nd April 2021
/**
 * BinEvents is an application that determines the bin number for each event and saves it to the ROOT file
 * @param 1 Name of ROOT file with B events
 * @param 2 Name of TTree
 * @param 3 Number of bins
 * @param 4 Name of ROOT output file
 * @param 5 Year of dataset
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
  TFile Infile(argv[1], "READ");
  TTree *Tree = nullptr;
  Infile.GetObject(argv[2], Tree);
  std::cout << "Input file ready\n";
  std::cout << "Creating output ROOT file...";
  TFile Outfile(argv[4], "RECREATE");
  TTree *OutTree = Tree->CloneTree(0);
  int BinNumber;
  OutTree->Branch("BinNumber", &BinNumber, "BinNumber/I");
  int NumberBins = std::atoi(argv[3]);
  std::cout << "Output ROOT file ready\n";
  std::cout << "Booking variables...";
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
  if(std::stoi(argv[5]) == 2011 || std::stoi(argv[5]) == 2012) {
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_0_PX", DaughterMomenta.data() + 12);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_0_PY", DaughterMomenta.data() + 13);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_0_PZ", DaughterMomenta.data() + 14);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_0_PE", DaughterMomenta.data() + 15);
  } else {
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PX", DaughterMomenta.data() + 12);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PY", DaughterMomenta.data() + 13);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PZ", DaughterMomenta.data() + 14);
    Tree->SetBranchAddress("Bu_constD0PV_D0_piplus_1_PE", DaughterMomenta.data() + 15);
  }
  std::cout << "Variables ready\n";
  std::cout << "Preparing binning scheme...\n";
  AmplitudePhaseSpace aph(NumberBins);
  if(NumberBins == 4) {
    aph.SetBinEdges(std::vector<double>{1.20923});
  } else if(NumberBins == 6) {
    aph.SetBinEdges(std::vector<double>{0.645101, 1.72065});
  } else if(NumberBins == 8) {
    aph.SetBinEdges(std::vector<double>{0.458065, 1.15464, 2.09644});
  }
  std::cout << "Ready to bin events\n";
  std::cout << "Binning events...\n";
  for(int i = 0; i < Tree->GetEntries(); i++) {
    Tree->GetEntry(i);
    std::vector<double> P(DaughterMomenta.begin(), DaughterMomenta.end());
    std::transform(P.begin(), P.end(), P.begin(), [](double &p) {return p/1000.0;});
    BinNumber = aph.WhichBin(Event(P));
    OutTree->Fill();
  }
  OutTree->Write();
  Outfile.Close();
  Infile.Close();
  std::cout << "Events are placed in their respective bins\n";
  return 0;
}
