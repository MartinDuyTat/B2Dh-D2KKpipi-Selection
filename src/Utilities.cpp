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

  std::string DetermineTransformation(std::string Expression) {
    if(Expression.substr(0, 7) == "log(1 -") {
      // If transformation is "log(1 - x)
      // Remove first 8 characters and last character to get variable name
      std::string variable = Expression.erase(0, 8);
      variable.erase(variable.size() - 1);
      return "log(1 - x) " + variable;
    } else if(Expression.substr(0, 8) == "log(min(") {
      // If transformation is "log(min(x, y))
      // First split up string by whitespace
      std::istringstream ss(Expression);
      std::string FirstPart, SecondPart;
      ss >> FirstPart;
      ss >> SecondPart;
      // Remove first 8 characters and last character of first part
      std::string variable1 = FirstPart.erase(0, 8);
      variable1.erase(variable1.size() - 1);
      // Remove last 2 characters of second part
      std::string variable2 = SecondPart.erase(SecondPart.size() - 2);
      return "log(min( " + variable1 + " " + variable2;
    } else if(Expression.substr(0, 8) == "log(max(") {
      // If transformation is "log(max(x, y))
      // First split up string by whitespace
      std::istringstream ss(Expression);
      std::string FirstPart, SecondPart;
      ss >> FirstPart;
      ss >> SecondPart;
      // Remove first 8 characters and last character of first part
      std::string variable1 = FirstPart.erase(0, 8);
      variable1.erase(variable1.size() - 1);
      // Remove last 2 characters of second part
      std::string variable2 = SecondPart.erase(SecondPart.size() - 2);
      return "log(max( " + variable1 + " " + variable2;
    } else if(Expression.substr(0, 4) == "log(") {
      // If transformation is "log(x)
      // Remove first 4 characters and last character to get varables name
      std::string variable = Expression.erase(0, 4);
      variable.erase(variable.size() - 1);
      return "log(x) " + variable;
    } else {
      // If there is no transformation
      return "None " + Expression;
    }
  }

}
