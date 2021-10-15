// Martin Duy Tat 26th February 2021
/**
 * Utilities is a namespace with a few useful functions
 */
#include<string>
#include<memory>
#include"TChain.h"
#include"TMVA/DataLoader.h"
#include"BaseCuts.h"

namespace Utilities {
  /**
   * LoadChain is a function for creating and loading a TChain
   * @param Chain TChain we want to add files to
   * @param NumberFiles Number of files to add to TChainn
   * @param Filename ROOT filename, can put in wildcards to TChain
   * @param BDecayMode Input "pi" for \f$B\to D\pi\f$ and "K" for \f$B\to DK\f$
   * @param DDecayMode Input "KKpipi" for \f$D\to KK\pi\pi\f$ and "Kpipipi" for \f$D\to K\pi\pi\pi\f$
   * @param BranchFilename Text file with list of branches to keep
   */
  void LoadChain(TChain *Chain, const std::string &Filename, const std::string &BDecayMode, const std::string &DDecayMode, const std::string &BranchFilename);
  /**
   * LoadCuts is a function for picking the correct cuts
   * @param CutType User input string with cut type
   * @return A smart pointer with the cut object
   */
  std::unique_ptr<BaseCuts> LoadCuts(std::string CutType, const std::string &DecayMode, const std::string &DDecayMode, int Year);
  /**
   * LoadTrainingVariables is a function that loads all the training variables for the BDT, to change the variables used in BDT training please change this function
   * @param DataLoader DataLoader object that is used for the BDT training
   * @param Filename Filename of text file with training variables
   */
  void LoadTrainingVariables(TMVA::DataLoader *DataLoader, std::string Filename);
  /**
   * A helper function for rearranging a list of daughter momenta so that they end up in the order K+ K- pi+ pi-
   * @param DaughterIDs A vector with the four daughter IDs in the same order as the momenta
   * @param DaughterMomenta A vector with the four daughter momenta
   */
  void RearrangeDaughterMomenta(std::vector<double> &DaughterIDs, std::vector<double> &DaughterMomenta);
}
