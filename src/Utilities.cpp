// Martin Duy Tat 26th February 2021

#include<string>
#include<iostream>
#include"TChain.h"
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

  void LoadTrainingVariables(TMVA::DataLoader *DataLoader) {
    DataLoader->AddVariable("Bu_PTASY_1.5",'F');
    DataLoader->AddVariable("log(Bach_PT)", 'F');
    DataLoader->AddVariable("log(Bu_RHO_BPV)", 'F');
    DataLoader->AddVariable("log(1 - Bu_DIRA_BPV)", 'F');
    DataLoader->AddVariable("log(1 - D0_DIRA_BPV)", 'F');
    DataLoader->AddVariable("log(D0_RHO_BPV)", 'F');
    DataLoader->AddVariable("log(Bu_P)", 'F');
    DataLoader->AddVariable("log(Bu_PT)", 'F');
    DataLoader->AddVariable("log(Bu_FDCHI2_OWNPV)", 'F');
    DataLoader->AddVariable("log(Bu_IPCHI2_OWNPV)", 'F');
    DataLoader->AddVariable("Bu_MAXDOCA", 'F');
    DataLoader->AddVariable("log(Bach_P)", 'F');
    DataLoader->AddVariable("log(Bach_IPCHI2_OWNPV)", 'F');
    DataLoader->AddVariable("log(D0_IPCHI2_OWNPV)", 'F');
    DataLoader->AddVariable("log(min(h1_IPCHI2_OWNPV, h2_IPCHI2_OWNPV))", 'F');
    DataLoader->AddVariable("log(min(h3_IPCHI2_OWNPV, h4_IPCHI2_OWNPV))", 'F');
    DataLoader->AddVariable("log(max(h1_P, h2_P))", 'F');
    DataLoader->AddVariable("log(max(h3_P, h4_P))", 'F');
    DataLoader->AddVariable("D0_MAXDOCA", 'F');
    DataLoader->AddVariable("log(max(h1_PT, h2_PT))", 'F');
    DataLoader->AddVariable("log(max(h3_PT, h4_PT))", 'F');
    DataLoader->AddVariable("BDToutput", 'F');
    return;
  }

}
