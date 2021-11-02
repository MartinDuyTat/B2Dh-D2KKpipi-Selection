// Martin Duy Tat 8th March 2021
/**
 * RemoveMultipleCandidates is an application that removes multiple candidates randomly
 * It first shuffles all the events, then goes through them one by one and keeps the first one for each event number
 * @param 1 ROOT filename with data sample
 * @param 2 ROOT filename with output sample
 * @param 3 Seed for picking random candidate (by default it is 9999)
 */

#include<iostream>
#include<string>
#include<numeric>
#include<random>
#include<algorithm>
#include"TFile.h"
#include"TTree.h"

int main(int argc, char *argv[]) {
  if(argc != 3 && argc != 4) {
    std::cout << "Please input 2 or 3 arguments\n";
    return 0;
  }
  std::cout << "Removing multiple candidates\n";
  std::cout << "Loading data...\n";
  TFile Infile(argv[1], "READ");
  TTree *InTree = nullptr;
  Infile.GetObject("DecayTree", InTree);
  std::cout << "Data sample ready\n";
  std::cout << "Creating output TTree...\n";
  TFile OutputFile(argv[2], "RECREATE");
  TTree *Tree = InTree->CloneTree(0);
  std::cout << "TTree ready\n";
  std::cout << "Shuffling events...\n";
  int N = InTree->GetEntries();
  std::vector<int> EventOrder(N);
  std::iota(EventOrder.begin(), EventOrder.end(), 0);
  int Seed = argc == 3 ? 9999 : std::stoi(argv[3]);
  auto rng = std::default_random_engine(Seed);
  std::shuffle(EventOrder.begin(), EventOrder.end(), rng);
  std::cout << "Event order now random\n";
  std::cout << "Going through data and keeping first candidates...\n";
  ULong64_t eventNumber;
  InTree->SetBranchAddress("eventNumber", &eventNumber);
  std::vector<int> EventNumbers;
  InTree->LoadBaskets();
  for(int i = 0; i < N; i++) {
    InTree->GetEntry(EventOrder[i]);
    if(std::find(EventNumbers.begin(), EventNumbers.end(), eventNumber) == EventNumbers.end()) {
      EventNumbers.push_back(eventNumber);
    } else {
      continue;
    }
    Tree->Fill();
  }
  Tree->Write();
  OutputFile.Write();
  OutputFile.Close();
  Infile.Close();
  std::cout << "No more multiple candidates\n";
  return 0;
}
