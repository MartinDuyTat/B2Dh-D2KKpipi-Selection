// Martin Duy Tat 22nd April 2021
/**
 * BinEvents is an application that determines the bin number for each event and saves it to the ROOT file
 * @param 1 Name of ROOT file with B events
 * @param 2 Name of ROOT output file
 * @param 3 Filename of text file with prefixes of daughter momenta in ntuple
 * @param 4 Units of daughter momenta, "GeV" or "MeV"
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

std::string ReplaceSubstring(std::string Line, const std::string &From, const std::string &To) {
  std::string::size_type Start = Line.find(From);
  if(Start == std::string::npos) {
    return Line;
  }
  Line.replace(Start, From.length(), To);
  return Line;
}

int main(int argc, char *argv[]) {
  if(argc != 5) {
    std::cout << "Need 4 input arguments\n";
    return 0;
  }
  std::cout << "Loading ROOT input file...\n";
  TFile Infile(argv[1], "READ");
  TTree *Tree = nullptr;
  Infile.GetObject("DecayTree", Tree);
  std::cout << "Input file ready\n";
  std::cout << "Creating output ROOT file...\n";
  TFile Outfile(argv[2], "RECREATE");
  TTree *OutTree = Tree->CloneTree(0);
  int BinNumber_4Bins, BinNumber_6Bins, BinNumber_8Bins;
  OutTree->Branch("BinNumber_4Bins", &BinNumber_4Bins, "BinNumber_4Bins/I");
  OutTree->Branch("BinNumber_6Bins", &BinNumber_6Bins, "BinNumber_6Bins/I");
  OutTree->Branch("BinNumber_8Bins", &BinNumber_8Bins, "BinNumber_8Bins/I");
  std::cout << "Output ROOT file ready\n";
  std::cout << "Booking variables...\n";
  std::vector<double> DaughterMomenta(16);
  std::vector<double> DaughterIDs(4);
  std::ifstream DaughterNameFile(argv[3]);
  std::string IDName;
  std::vector<std::string> PP(4);
  DaughterNameFile >> IDName >> PP[0] >> PP[1] >> PP[2] >> PP[3];
  for(int i = 0; i < 4; i++) {
    std::string DaughterName;
    DaughterNameFile >> DaughterName;
    std::string NewDaughterName = ReplaceSubstring(DaughterName, "**", IDName);
    Tree->SetBranchAddress(NewDaughterName.c_str(), DaughterIDs.data() + i);
    for(int j = 0; j < 4; j++) {
      std::string NewDaughterName = ReplaceSubstring(DaughterName, "**", PP[j]);
      Tree->SetBranchAddress(NewDaughterName.c_str(), DaughterMomenta.data() + j + 4*i);
    }
  }
  DaughterNameFile.close();
  std::cout << "Variables ready\n";
  std::cout << "Preparing binning scheme...\n";
  AmplitudePhaseSpace aph4(4), aph6(6), aph8(8);
  aph4.SetBinEdges(std::vector<double>{1.20923});
  aph6.SetBinEdges(std::vector<double>{0.645101, 1.72065});
  aph8.SetBinEdges(std::vector<double>{0.458065, 1.15464, 2.09644});
  aph4.UseVariableBinWidths(true);
  aph6.UseVariableBinWidths(true);
  aph8.UseVariableBinWidths(true);
  aph4.SetKSVeto(0.477, 0.507);
  aph6.SetKSVeto(0.477, 0.507);
  aph8.SetKSVeto(0.477, 0.507);
  std::cout << "Ready to bin events\n";
  std::cout << "Binning events...\n";
  for(int i = 0; i < Tree->GetEntries(); i++) {
    Tree->GetEntry(i);
    if(std::find(DaughterIDs.begin(), DaughterIDs.end(), 0) != DaughterIDs.end()) {
      BinNumber_4Bins = 0;
      BinNumber_6Bins = 0;
      BinNumber_8Bins = 0;
      continue;
    }
    Utilities::RearrangeDaughterMomenta(DaughterIDs, DaughterMomenta);
    std::vector<double> P(DaughterMomenta.begin(), DaughterMomenta.end());
    if(std::string(argv[4]) == "MeV") {
      std::transform(P.begin(), P.end(), P.begin(), [](double &p) {return p/1000.0;});
    }
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
