// Martin Duy Tat
/**
 * BDTClassifier is an application that classifies events in a sample using a BDTG
 * @param 1 Filename of XML file with the BDT weights
 * @param 2 Filename of text file with list of training variables
 * @param 3 Filename of ROOT file with datasample
 * @param 4 Filename of output file with BDT classifier output, saved in a TTree
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
  std::cout << "Loading TMVA and booking BDTG classifier...\n";
  TMVA::Reader *Classifier = new TMVA::Reader("!Color:!Silent");
  std::cout << "Loading branch and classifier variables...\n";
  BDTVariables Variables{std::string(argv[2])};
  Variables.SetTreeBranchAddresses(InputData);
  Variables.SetClassifierBranchAddresses(Classifier);
  std::cout << "Branch and classifier variables connected\n";
  Classifier->BookMVA("BDTG method", TString(argv[1]));
  std::cout << "Classifier ready to classify\n";
  std::cout << "Loading BDT output file...\n";
  TFile OutputFile(argv[4], "RECREATE");
  TTree BDTTree("BDTG", "BDTG outputs");
  Double_t BDToutput;
  BDTTree.Branch("BDToutput", &BDToutput);
  std::cout << "BDT output tree ready\n";
  for(Long64_t i = 0; i < InputData->GetEntries(); i++) {
    if(i%1000 == 0) {
      std::cout << "Processing event " << i << std::endl;
    }
    InputData->GetEntry(i);
    Variables.UpdateVariables();
    BDToutput = Classifier->EvaluateMVA("BDTG method");
    BDTTree.Fill();
  }
  std::cout << "Classified all events\n";
  BDTTree.Write();
  OutputFile.Close();
  InputFile.Close();
  delete Classifier;
  std::cout << "Congratulations, all background has been killed!\n";
  return 0;
}