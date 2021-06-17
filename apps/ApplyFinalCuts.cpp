// Martin Duy Tat 8th March 2021
/**
 * ApplyFinalCuts takes in a ROOT file with a data sample and a ROOT file with the BDT output
 * It creates a new ROOT file with a selection of the events based on final cuts
 * It also recreates the branch Bu_constD0PV_M so that it is no longer an array
 * @param 1 ROOT filename with data sample
 * @param 2 Input "pi" for \f$B\to D\pi\f$ and "K" for \f$B\to DK\f$
 * @param 3 Input "yes" to omit cut on flight significance
 * @param 4 Filename of output ROOT file
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
  if(argc != 5) {
    std::cout << "Please input 4 arguments\n";
    return 0;
  }
  std::cout << "Final event selection\n";
  TFile InputData(argv[1], "READ");
  TTree *InputTree = nullptr;
  InputData.GetObject("DecayTree", InputTree);
  std::cout << "Applying selection...\n";
  FinalCuts Cuts{std::string(argv[2])};
  if(std::string(argv[3]) == "yes") {
    Cuts = FinalCuts{std::string(argv[2]), 0.75, true, true, false, false};
  }
  ApplyCuts applyCuts(Cuts.GetCuts(), true);
  TFile OutputFile(argv[4], "RECREATE");
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
