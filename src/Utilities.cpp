// Martin Duy Tat 26th February 2021

#include<string>
#include<iostream>
#include<fstream>
#include"TChain.h"
#include"TString.h"
#include"TMVA/DataLoader.h"
#include"BaseCuts.h"
#include"TruthMatchingCuts.h"
#include"HighBMassCut.h"

namespace Utilities {
  void LoadChain(TChain *Chain, int NumberFiles, std::string Filename, std::string DecayMode) {
    std::cout << "Initializing TChain...\n";
    if(DecayMode == "pi") {
      Chain->SetName("B2DPi_D2KKPiPi/DecayTree");
    } else if(DecayMode == "K") {
      Chain->SetName("B2DK_D2KKPiPi/DecayTree");
    } else {
      std::cout << "Decay mode " << DecayMode << " unknown\n";
      return;
    }
    std::cout << "TChain initialized\n";
    std::cout << "Loading input files...\n";
    if(NumberFiles == 0) {
      std::cout << "Need more than 0 input files\n";
      return;
    }
    if(NumberFiles == 1) {
      Chain->Add(Filename.c_str());
    } else {
      for(int i = 0; i < NumberFiles; i++) {
	Chain->Add((Filename + std::to_string(i) + ".root").c_str());
      }
    }
    std::cout << "ROOT files added to TChain\n";
    return;
  }

  std::unique_ptr<BaseCuts> LoadCuts(std::string CutType, std::string DecayMode, int Year) {
    if(CutType == "SignalTraining") {
      return std::unique_ptr<BaseCuts>{new TruthMatchingCuts{DecayMode, Year}};
    } else if(CutType == "BackgroundTraining") {
      return std::unique_ptr<BaseCuts>{new HighBMassCut{Year}};
    } else if(CutType == "PrepareBDT") {
      return std::unique_ptr<BaseCuts>{new BaseCuts{Year}};
    } else {
      std::cout << "Cut type not recognized\n";
      return std::unique_ptr<BaseCuts>{nullptr};
    }
  }

  void LoadTrainingVariables(TMVA::DataLoader *DataLoader, std::string Filename) {
    std::ifstream TrainingVariablesFile(Filename);
    if(TrainingVariablesFile.is_open()) {
      std::string line;
      while(std::getline(TrainingVariablesFile, line)) {
	DataLoader->AddVariable(TString(line), 'F');
      }
      TrainingVariablesFile.close();
    }
    return;
  }

}
