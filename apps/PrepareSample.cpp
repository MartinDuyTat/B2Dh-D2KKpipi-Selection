// Martin Duy Tat 25th February 2021
/**
 * PrepareSample takes in a ROOT file from DaVinci and creates a new ROOT file with a selection of the events based on cuts
 * The possible cut options are:
 * "SignalTraining", the standard base cuts and MC truth matching cuts to prepare a signal training sample for the BDT
 * "SignalTrainingSmeared", the standard base cuts and MC truth matching cuts to prepare a signal training sample for the BDT, but with smearing of the B mass (for fitting the mass shape)
 * "BackgroundTraining", the standard base cuts but the \f$B\f$ mass is between \f$5800\f$MeV and \f$7000\f$ MeV to prepare a background sample for the BDT
 * "CombinatorialBackground", the standard base cuts but the \f$B\f$ mass is between \f$5600\f$MeV and \f$6500\f$ MeV to study combinatorial background
 * "PrepareBDT", the standard base cuts before applying a BDT
 * "PrepareCharmless", similar to "PrepareBDT" but picks out the lower D mass sideband
 * "KpipipiSingleMisID", the standard base cuts and MC truth matching with single mis-ID of Kpipipi to KKpipi
 * "Kpipipipi0SingleMisID", the standard base cuts and MC truth matching with single mis-ID of Kpipipipi0 to KKpipi
 * "KpipipiTripleMisID", the standard base cuts and MC truth matching with triple mis-ID of pipikpi to KKpipi
 * @param 1 Cut type as described above
 * @param 2 Filename of ROOT file, can have wild cards
 * @param 3 Input "pi" for \f$B\to D\pi\f$ and "K" for \f$B\to DK\f$
 * @param 4 Year of dataset
 * @param 5 D decay mode, "KKpipi", "pipipipi" or "Kpipipi"
 * @param 6 Filename of output ROOT file
 * @param 7 Text file with list of branches to keep
 * @param 8 Amount of smearing in MeV
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
  if(argc != 8 && argc != 9) {
    std::cout << "Please input 7 or 8 arguments\n";
    return 0;
  }
  std::string CutType(argv[1]);
  std::string Filename(argv[2]);
  std::string BDecayMode(argv[3]);
  int Year = std::atoi(argv[4]);
  std::string DDecayMode(argv[5]);
  std::string OutputFilename(argv[6]);
  std::string BranchFile(argv[7]);
  std::cout << "Preparing sample with the " << argv[1] << " cuts\n";
  TChain Chain;
  Utilities::LoadChain(&Chain, Filename, BDecayMode, CutType == "Kpipipipi0SingleMisID" ? "KKpipi" : DDecayMode, BranchFile);
  std::cout << "Applying selection...\n";
  std::unique_ptr<BaseCuts> Cuts = Utilities::LoadCuts(CutType, BDecayMode, DDecayMode, Year);
  ApplyCuts applyCuts(Cuts->GetCuts());
  if(CutType == "SignalTrainingSmeared" && argc == 9) {
    applyCuts = ApplyCuts(Cuts->GetCuts(), false, std::atof(argv[8]));
  }
  TFile OutputFile(OutputFilename.c_str(), "RECREATE");
  TTree *OutputTree = applyCuts(&Chain);
  OutputTree->SetAlias("zSig", "(D0_ENDVERTEX_Z - Bu_ENDVERTEX_Z)/(sqrt(D0_ENDVERTEX_ZERR*D0_ENDVERTEX_ZERR + Bu_ENDVERTEX_ZERR*Bu_ENDVERTEX_ZERR))");
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
