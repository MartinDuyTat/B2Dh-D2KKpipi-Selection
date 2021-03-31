// Martin Duy Tat 8th March 2021
/**
 * ApplyFinalCuts takes in a ROOT file with a data sample and a ROOT file with the BDT output
 * It creates a new ROOT file with a selection of the events based on final cuts
 * It also recreates the branch Bu_constD0PV_M so that it is no longer an array
 * @param 1 ROOT filename with data sample
 * @param 2 ROOT filename with BDToutput
 * @param 3 Input "pi" for \f$B\to D\pi\f$ and "K" for \f$B\to DK\f$
 * @param 4 Input "yes" to omit cut on flight significance and DecayTreeFitter \f$\chi^2\f$ for charmless backgrounds study
 * @param 5 Filename of output ROOT file
 */

#include<iostream>
#include<string>
#include<stdlib.h>
#include<memory>
#include"TChain.h"
#include"TFile.h"
#include"FinalCuts.h"
#include"ApplyCuts.h"
#include"Utilities.h"

int main(int argc, char *argv[]) {
  if(argc != 6) {
    std::cout << "Please input 5 arguments\n";
    return 0;
  }
  std::cout << "Final event selection\n";
  TFile InputData(argv[1], "READ");
  TTree *InputTree = nullptr;
  InputData.GetObject("DecayTree", InputTree);
  TFile BDTFile(argv[2], "READ");
  TTree *BDTTree = nullptr;
  BDTFile.GetObject("BDTG", BDTTree);
  InputTree->AddFriend(BDTTree);
  std::cout << "Applying selection...\n";
  FinalCuts Cuts{std::string(argv[3])};
  if(std::string(argv[4]) == "yes") {
    Cuts = FinalCuts{std::string(argv[3]), 0.75, true, true, false, false};
  }
  ApplyCuts applyCuts(Cuts.GetCuts(), true);
  TFile OutputFile(argv[5], "RECREATE");
  TTree *OutputTree = applyCuts(InputTree);
  std::cout << "TTree with selection ready...\n";
  std::cout << "Saving file...\n";
  OutputTree->SetDirectory(&OutputFile);
  OutputTree->Write();
  OutputFile.Close();
  std::cout << "TTree with selection saved to file\n";
  std::cout << "Final selection ready!\n";
  return 0;
}
