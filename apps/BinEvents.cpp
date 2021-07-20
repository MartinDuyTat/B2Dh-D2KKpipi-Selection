// Martin Duy Tat 22nd April 2021
/**
 * BinEvents is an application that determines the bin number for each event and saves it to the ROOT file
 * @param 1 Name of ROOT file with B events
 * @param 2 Name of TTree
 * @param 3 Name of ROOT output file
 * @param 4 Year of dataset
 * @param 5 Filename of text file with prefixes of daughter momenta in ntuple
 */

#include<iostream>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include"TBranch.h"
#include"TFile.h"
#include"TTree.h"
#include"Event.h"
#include"Utilities.h"
#include"AmplitudePhaseSpace.h"

int main(int argc, char *argv[]) {
  if(argc != 6) {
    std::cout << "Need 5 input arguments\n";
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
  std::vector<Float_t> DaughterMomenta(16);
  std::vector<Float_t> DaughterIDs(4);
  std::ifstream PrefixFile(argv[5]);
  for(int i = 0; i < 4; i++) {
    std::string DaughterPrefix;
    PrefixFile >> DaughterPrefix;
    Tree->SetBranchAddress((DaughterPrefix + "_ID").c_str(), DaughterIDs.data() + i);
    std::vector<std::string> PP{"_PX", "_PY", "_PZ", "_PE"};
    for(int j = 0; j < 4; j++) {
      Tree->SetBranchAddress((DaughterPrefix + PP[j]).c_str(), DaughterMomenta.data() + j + 4*i);
    }
  }
  PrefixFile.close();
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
    Utilities::RearrangeDaughterMomenta(DaughterIDs, DaughterMomenta);
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
