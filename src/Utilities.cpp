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
#include"CombinatorialBMassCut.h"
#include"CharmlessCuts.h"

namespace Utilities {
  void LoadChain(TChain *Chain, const std::string &Filename, const std::string &BDecayMode, const std::string &DDecayMode, const std::string &BranchFilename) {
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
    } else if(DDecayMode == "pipipipi") {
      if(BDecayMode == "pi") {
	Chain->SetName("B2DPi_D2PiPiPiPi/DecayTree");
      } else if(BDecayMode == "K") {
	Chain->SetName("B2DK_D2PiPiPiPi/DecayTree");
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
    Chain->Add(Filename.c_str());
    std::cout << "ROOT files added to TChain\n";
    Chain->SetBranchStatus("*", 0);
    std::ifstream BranchFile(BranchFilename);
    std::string word;
    std::cout << "The following branches are activated:\n";
    while(BranchFile >> word) {
      Chain->SetBranchStatus(word.c_str(), 1);
      std::cout << word << "\n";
    }
    BranchFile.close();
  }

  std::unique_ptr<BaseCuts> LoadCuts(std::string CutType, const std::string &DecayMode, const std::string &DDecayMode, int Year) {
    if(CutType == "SignalTraining") {
      return std::unique_ptr<BaseCuts>{new TruthMatchingCuts{DecayMode, DDecayMode, Year}};
    } else if(CutType == "SignalTrainingSmeared") {
      return std::unique_ptr<BaseCuts>{new TruthMatchingCuts{DecayMode, DDecayMode, Year, "", true, true, true, true, true, false}};
    } else if(CutType == "KpipipiSingleMisID") {
      auto Cuts = std::unique_ptr<BaseCuts>{new TruthMatchingCuts{DecayMode, DDecayMode, Year, "Single", true, true, true, true, false, true}};
      Cuts->SetBMassName("Bu_constD0PV_SingleMisID_M");
      Cuts->SetDMassName("Bu_const_SingleMisID_D0_M");
      Cuts->SetDTFStatusName("0");
      return Cuts;
    } else if(CutType == "KpipipiTripleMisID") {
      auto Cuts = std::unique_ptr<BaseCuts>{new TruthMatchingCuts{DecayMode, DDecayMode, Year, "Triple", true, true, true, true, false, true}};
      Cuts->SetBMassName("Bu_constD0PV_TripleMisID_M");
      Cuts->SetDMassName("Bu_const_TripleMisID_D0_M");
      Cuts->SetDTFStatusName("0");
      return Cuts;
    } else if(CutType == "KpipipiTopipipipiMisID") {
      auto Cuts = std::unique_ptr<BaseCuts>{new TruthMatchingCuts{DecayMode, DDecayMode, Year, "pipipipi", true, true, true, true, false, true}};
      Cuts->SetBMassName("Bu_constD0PV_pipipipiMisID_M");
      Cuts->SetDMassName("Bu_const_pipipipiMisID_D0_M");
      Cuts->SetDTFStatusName("0");
      return Cuts;
    } else if(CutType == "BackgroundTraining") {
      return std::unique_ptr<BaseCuts>{new HighBMassCut{DDecayMode, Year}};
    } else if(CutType == "CombinatorialBackground") {
      return std::unique_ptr<BaseCuts>{new CombinatorialBMassCut{DDecayMode, Year}};
    } else if(CutType == "PrepareBDT") {
      return std::unique_ptr<BaseCuts>{new BaseCuts{DDecayMode, Year}};
    } else if(CutType == "PrepareCharmless") {
      return std::unique_ptr<BaseCuts>{new CharmlessCuts{DDecayMode, Year}};
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
  }

  void RearrangeDaughterMomenta(std::vector<double> &DaughterIDs, std::vector<double> &DaughterMomenta) {
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
