// Martin Duy Tat 26th February 2021
/**
 * Utilities is a namespace with a few useful functions
 */
#include<string>
#include<memory>
#include"TChain.h"
#include"BaseCuts.h"

namespace Utilities {
  /**
   * LoadChain is a function for creating and loading a TChain
   * @param Chain TChain we want to add files to
   * @param NumberFiles Number of files to add to TChainn
   * @param Filename If there's a single input file, input full path name, otherwise input the path name without the number and file extension (e.g. if filenames are myfile0.root, myfile1.root, etc input myfile)
   * @param DecayMode Input "pi" for \f$B\to D\pi\f$ and "K" for \f$B\to DK\f$
   */
  void LoadChain(TChain *Chain, int NumberFiles, std::string Filename, std::string DecayMode);
  /**
   * LoadCuts is a function for picking the correct cuts
   * @param CutType User input string with cut type
   * @return A smart pointer with the cut object
   */
  std::unique_ptr<BaseCuts> LoadCuts(std::string CutType, std::string DecayMode, int Year);
}
