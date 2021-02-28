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
  /**
   * LoadTrainingVariables is a function that loads all the training variables for the BDT, to change the variables used in BDT training please change this function
   * @param DataLoader DataLoader object that is used for the BDT training
   * @param Filename Filename of text file with training variables
   */
  void LoadTrainingVariables(TMVA::DataLoader *DataLoader, std::string Filename);
  /**
   * DetermineTransformation takes in a string with a mathematical expression and determines what the variable transformation is
   * Only "None", "log(x)", "log(1 - x)", "log(max(x, y))" and "log(min(x, y))" is currently supported
   * @param Expression Mathematical expression we want to determine the transformation of
   * @return A space separated list of strings, where the first string identifies the transformation (as described above), the second string is the variable name and the third string is the second variable in the "log(max(x, y))" and "log(min(x, y))" cases
   */
  std::string DetermineTransformation(std::string Expression);
}
