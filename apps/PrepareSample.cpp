// Martin Duy Tat 25th February 2021
/**
 * PrepareSample takes in a ROOT file from DaVinci and creates a new ROOT file with a selection of the events based on cuts
 * The possible cut options are:
 * "SignalTraining", the standard base cuts and MC truth matching cuts to prepare a signal training sample for the BDT
 * "BackgroundTraining", the standard base cuts but the \f$B\f$ mass is between \f$5800\f$MeV and \f$7000\f$ MeV to prepare a background sample for the BDT
 * "PrepareBDT", the standard base cuts before applying a BDT
 * "PrepareCharmless", similar to "PrepareBDT" but picks out the lower D mass sideband
 * "KpipipiSingleMisID", the standard base cuts and MC truth matching with single mis-ID of Kpipipi to KKpipi
 * "KpipipiTripleMisID", the standard base cuts and MC truth matching with triple mis-ID of pipikpi to KKpipi
 * @param 1 Cut type as described above
 * @param 2 Number of input files
 * @param 3 If there's a single input file, input full path name, otherwise input the path name without the number and file extension (e.g. if filenames are myfile0.root, myfile1.root, etc input myfile)
 * @param 4 Input "pi" for \f$B\to D\pi\f$ and "K" for \f$B\to DK\f$
 * @param 5 Year of dataset
 * @param 6 D decay mode
 * @param 7 Filename of output ROOT file
 * @param 8 Text file with list of branches to keep
 */

#include<iostream>
#include<string>
#include<stdlib.h>
#include<memory>
#include"TChain.h"
#include"TFile.h"
#include"BaseCuts.h"
#include"ApplyCuts.h"
#include"Utilities.h"

int main(int argc, char *argv[]) {
  if(argc != 9) {
    std::cout << "Please input 8 arguments\n";
    return 0;
  }
  std::string CutType(argv[1]);
  int NFiles = std::atoi(argv[2]);
  std::string Filename(argv[3]);
  std::string BDecayMode(argv[4]);
  int Year = std::atoi(argv[5]);
  std::string DDecayMode(argv[6]);
  std::string OutputFilename(argv[7]);
  std::string BranchFile(argv[8]);
  std::cout << "Preparing sample with the " << argv[1] << " cuts\n";
  TChain Chain;
  Utilities::LoadChain(&Chain, NFiles, Filename, BDecayMode, DDecayMode, BranchFile);
  std::cout << "Applying selection...\n";
  std::unique_ptr<BaseCuts> Cuts = Utilities::LoadCuts(CutType, BDecayMode, DDecayMode, Year);
  ApplyCuts applyCuts(Cuts->GetCuts());
  TFile OutputFile(OutputFilename.c_str(), "RECREATE");
  TTree *OutputTree = applyCuts(&Chain);
  std::cout << "TTree with selection ready...\n";
  std::cout << "Saving file...\n";
  OutputTree->SetDirectory(&OutputFile);
  OutputTree->Write();
  OutputTree->SetDirectory(0);
  OutputFile.Close();
  delete OutputTree;
  std::cout << "TTree with selection saved to file\n";
  std::cout << "Signal training sample ready!\n";
  return 0;
}
