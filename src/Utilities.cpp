// Martin Duy Tat 26th February 2021

#include<string>
#include<iostream>
#include<fstream>
#include<algorithm>
#include"TChain.h"
#include"TString.h"
#include"TMVA/DataLoader.h"
#include"BaseCuts.h"
#include"TruthMatchingCuts.h"
#include"HighBMassCut.h"
#include"CharmlessCuts.h"

namespace Utilities {
  void LoadChain(TChain *Chain, int NumberFiles, const std::string &Filename, const std::string &BDecayMode, const std::string &DDecayMode) {
    std::cout << "Initializing TChain...\n";
    if(DDecayMode == "KKpipi") {
      if(BDecayMode == "pi") {
	Chain->SetName("B2DPi_D2KKPiPi/DecayTree");
      } else if(BDecayMode == "K") {
	Chain->SetName("B2DK_D2KKPiPi/DecayTree");
      } else {
	std::cout << "Decay mode " << BDecayMode << " unknown\n";
	return;
      }
    } else if(DDecayMode == "Kpipipi") {
      if(BDecayMode == "pi") {
	Chain->SetName("B2DPi_D2KPiPiPi/DecayTree");
      } else if(BDecayMode == "K") {
	Chain->SetName("B2DK_D2KPiPiPi/DecayTree");
      } else {
	std::cout << "Decay mode " << BDecayMode << " unknown\n";
	return;
      }
    } else {
      std::cout << "Decay mode " << DDecayMode << " unknown\n";
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
    } else if(CutType == "KpipipiSingleMisID") {
      auto Cuts = std::unique_ptr<BaseCuts>{new TruthMatchingCuts{DecayMode, Year, "Single", true, true, true, true, false, true}};
      Cuts->SetBMassName("Bu_constD0PV_SingleMisID_M");
      Cuts->SetDMassName("Bu_const_SingleMisID_D0_M");
      Cuts->SetDTFStatusName("0");
      return Cuts;
    } else if(CutType == "KpipipiTripleMisID") {
      auto Cuts = std::unique_ptr<BaseCuts>{new TruthMatchingCuts{DecayMode, Year, "Triple", true, true, true, true, false, true}};
      Cuts->SetBMassName("Bu_constD0PV_TripleMisID_M");
      Cuts->SetDMassName("Bu_const_TripleMisID_D0_M");
      Cuts->SetDTFStatusName("0");
      return Cuts;
    } else if(CutType == "BackgroundTraining") {
      return std::unique_ptr<BaseCuts>{new HighBMassCut{Year}};
    } else if(CutType == "PrepareBDT") {
      return std::unique_ptr<BaseCuts>{new BaseCuts{Year}};
    } else if(CutType == "PrepareCharmless") {
      return std::unique_ptr<BaseCuts>{new CharmlessCuts{Year}};
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

  void RearrangeDaughterMomenta(std::vector<float> &DaughterIDs, std::vector<float> &DaughterMomenta) {
    int KPlusIndex = std::find(DaughterIDs.begin(), DaughterIDs.end(), 321) - DaughterIDs.begin();
    if(KPlusIndex != 0) {
      std::swap(DaughterIDs[0], DaughterIDs[KPlusIndex]);
      std::swap_ranges(DaughterMomenta.begin() + 0, DaughterMomenta.begin() + 4, DaughterMomenta.begin() + 4*KPlusIndex);
    }
    int KMinusIndex = std::find(DaughterIDs.begin(), DaughterIDs.end(), -321) - DaughterIDs.begin();
    if(KMinusIndex != 1) {
      std::swap(DaughterIDs[1], DaughterIDs[KMinusIndex]);
      std::swap_ranges(DaughterMomenta.begin() + 4, DaughterMomenta.begin() + 8, DaughterMomenta.begin() + 4*KMinusIndex);
    }
    int piPlusIndex = std::find(DaughterIDs.begin(), DaughterIDs.end(), 211) - DaughterIDs.begin();
    if(piPlusIndex != 2) {
      std::swap(DaughterIDs[2], DaughterIDs[piPlusIndex]);
      std::swap_ranges(DaughterMomenta.begin() + 8, DaughterMomenta.begin() + 12, DaughterMomenta.begin() + 4*piPlusIndex);
    }
    int piMinusIndex = std::find(DaughterIDs.begin(), DaughterIDs.end(), -211) - DaughterIDs.begin();
    if(piMinusIndex != 3) {
      std::swap(DaughterIDs[3], DaughterIDs[piMinusIndex]);
      std::swap_ranges(DaughterMomenta.begin() + 12, DaughterMomenta.begin() + 16, DaughterMomenta.begin() + 4*piMinusIndex);
    }
  }

}
