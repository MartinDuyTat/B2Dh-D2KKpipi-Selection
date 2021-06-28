// Martin Duy Tat
/**
 * TrainBDT is an application that trains a BDT using signal and background samples
 * @param 1 Path to directory with signal ROOT files
 * @param 2 Path to directory with background ROOT files
 * @param 3 Filename of text file with list of training variables
 * @param 4 Name of BDT (outputfile will have the same name, with .root extension and the weight files will also have this name)
 */

#include<iostream>
#include<string>
#include"TChain.h"
#include"TCut.h"
#include"TString.h"
#include"TFile.h"
#include"TMVA/Factory.h"
#include"TMVA/DataLoader.h"
#include"Utilities.h"

int main(int argc, char *argv[]) {
  if(argc != 5) {
    std::cout << "Need 4 input arguments\n";
    return 0;
  }
  std::cout << "BDT training\n";
  std::cout << "Loading signal and background samples...\n";
  TChain SignalTree("DecayTree");
  SignalTree.Add((std::string(argv[1]) + "/*.root").c_str());
  TChain BackgroundTree("DecayTree");
  BackgroundTree.Add((std::string(argv[2]) + "/*.root").c_str());
  std::cout << "Training data loaded\n";
  std::cout << "Loading TMVA and booking BDTG...\n";
  TFile OutputFile((std::string(argv[4]) + ".root").c_str(), "RECREATE");
  std::string FactoryOptions("!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");
  TMVA::Factory Factory(TString(argv[4]), &OutputFile, TString(FactoryOptions));
  TMVA::DataLoader DataLoader = TMVA::DataLoader(TString(argv[4]));
  Utilities::LoadTrainingVariables(&DataLoader, std::string(argv[3]));
  DataLoader.AddTree(&SignalTree, "Signal", 1.0, "(eventNumber%2 == 1)", TMVA::Types::kTraining);
  DataLoader.AddTree(&SignalTree, "Signal", 1.0, "(eventNumber%2 == 0)", TMVA::Types::kTesting);
  DataLoader.AddTree(&BackgroundTree, "Background", 1.0, "eventNumber%2 == 1", TMVA::Types::kTraining);
  DataLoader.AddTree(&BackgroundTree, "Background", 1.0, "eventNumber%2 == 0", TMVA::Types::kTesting);
  std::string DataLoaderSettings("nTrain_Signal=0:nTrain_Background=0:NormMode=NumEvents:!V");
  TCut NoCuts;
  DataLoader.PrepareTrainingAndTestTree(NoCuts, NoCuts, DataLoaderSettings);
  std::string BDTSettings("!H:!V:NTrees=500:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2");
  Factory.BookMethod(&DataLoader, TMVA::Types::kBDT, "BDTG", TString(BDTSettings));
  std::cout << "Ready to train BDTG\n";
  Factory.TrainAllMethods();
  Factory.TestAllMethods();
  Factory.EvaluateAllMethods();
  OutputFile.Close();
  std::cout << "Congratulations, BDT is fit and ready!\n";
  return 0;
}
