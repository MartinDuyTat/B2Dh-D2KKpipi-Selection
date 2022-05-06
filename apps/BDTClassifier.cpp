// Martin Duy Tat
/**
 * BDTClassifier is an application that classifies events in a sample using a BDTG
 * @param 1 Filename of XML file with the BDT weights
 * @param 2 Filename of text file with list of training variables
 * @param 3 Filename of ROOT file with datasample
 * @param 4 Filename of ROOT file with BDT outputs, and a loose BDT cut at 0.0
 */

#include<iostream>
#include<string>
#include<map>
#include"TTree.h"
#include"TString.h"
#include"TFile.h"
#include"TMVA/Reader.h"
#include"Utilities.h"
#include"BDTVariables.h"

int main(int argc, char *argv[]) {
  if(argc != 5) {
    std::cout << "Need 4 input arguments\n";
    return 0;
  }
  std::cout << "BDT classification\n";
  std::cout << "Loading datasample...\n";
  TFile InputFile(argv[3], "READ");
  TTree *InputData = nullptr;
  InputFile.GetObject("DecayTree", InputData);
  std::cout << "Datasample ready for classification\n";
  std::cout << "Preparing output ROOT file\n";
  TFile OutputFile(argv[4], "RECREATE");
  TTree *OutputData = InputData->CloneTree(0);
  Double_t BDToutput;
  OutputData->Branch("BDToutput", &BDToutput);
  std::cout << "Output TTree ready\n";
  std::cout << "Loading TMVA and booking BDTG classifier...\n";
  TMVA::Reader *Classifier = new TMVA::Reader("!Color:!Silent");
  std::cout << "Loading branch and classifier variables...\n";
  BDTVariables Variables{std::string(argv[2])};
  Variables.SetTreeBranchAddresses(InputData);
  Variables.SetClassifierBranchAddresses(Classifier);
  std::cout << "Branch and classifier variables connected\n";
  Classifier->BookMVA("BDTG method", TString(argv[1]));
  std::cout << "Classifier ready to classify\n";
  for(Long64_t i = 0; i < InputData->GetEntries(); i++) {
    InputData->GetEntry(i);
    Variables.UpdateVariables();
    BDToutput = Classifier->EvaluateMVA("BDTG method");
    if(BDToutput > 0.0) {
      OutputData->Fill();
    }
  }
  std::cout << "Classified all events\n";
  OutputData->Write();
  OutputFile.Close();
  InputFile.Close();
  delete Classifier;
  std::cout << "Congratulations, all background has been swept under the carpet!\n";
  return 0;
}
