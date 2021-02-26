// Martin Duy Tat 25th Februrary 2021
/**
 * PrepareSignalTrainingSample takes in an MC sample ROOT file from DaVinci and saves new ROOT file with a signal training sample for the BDT
 * The cuts applied are the standard base cuts and MC truth matching cuts
 * @param 1 Number of input files
 * @param 2 If there's a single input file, input full path name, otherwise input the path name without the number and file extension (e.g. if filenames are myfile0.root, myfile1.root, etc input myfile)
 * @param 3 Input "Pi" for \f$B\to D\pi\f$ and "K" for \f$B\to DK\f$
 * @param 4 Year of dataset
 * @param 5 Filename of output ROOT file
 */

#include<iostream>
#include<string>
#include<stdlib.h>
#include"TChain.h"
#include"TFile.h"
#include"TruthMatchingCuts.h"
#include"ApplyCuts.h"

int main(int argc, char *argv[]) {
  if(argc != 5) {
    std::cout << "Please input 4 arguments\n";
    return 0;
  }
  std::cout << "Preparing signal training sample from an MC sample from DaVinci\n";
  std::cout << "Initializing TChain...";
  TChain *Chain;
  if(std::strcmp(argv[3], "Pi")) {
    Chain = new TChain("B2DPi_D2KKPiPi/DecayTree");
  } else if(std::strcmp(argv[3], "K")) {
    Chain = new TChain("B2DK_D2KKPiPi/DecayTree");
  } else {
    std::cout << "Decay mode " << argv[3] << " unknown\n";
    return 0;
  }
  if(std::atoi(argv[1]) == 0) {
    std::cout << "Need more than 0 input files\n";
    return 0;
  }
  if(std::atoi(argv[1]) == 1) {
    Chain.Add(argv[2]);
  } else {
    std::string FilenamePrefix(argv[2]);
    for(int i = 0; i < std::atoi(argv[1]); i++) {
      Chain.Add(FilenamePrefix + std::to_string(i) + ".root");
    }
  }
  TruthMatchingCuts Cuts(std::atoi(argv[4]), std::atoi(argv[4]));
  ApplyCuts applyCuts(Cuts.GetCuts());
  TFile OutputFile(argv[5], "RECREATE");
  TTree *OutputTree = applyCuts(Chain);
  OutputFile.Write();
  OutputFile.Close();
  return 0;
}
