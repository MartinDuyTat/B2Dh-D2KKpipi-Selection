// Martin Duy Tat 11th June 2021

#include<string>
#include<fstream>
#include<iostream>
#include"EventNumbers.h"
#include"TChain.h"

EventNumbers::EventNumbers(const std::string &Filename) {
  std::ifstream Infile(Filename);
  std::string line;
  TChain Chain("DecayTree");
  while(std::getline(Infile, line)) {
    Chain.Add(line.c_str());
  }
  Float_t Bu_constD0PV_M;
  ULong64_t EventNumber;
  Chain.SetBranchStatus("*", 0);
  Chain.SetBranchStatus("eventNumber", 1);
  Chain.SetBranchStatus("Bu_constD0PV_M", 1);
  Chain.SetBranchAddress("Bu_constD0PV_M", &Bu_constD0PV_M);
  Chain.SetBranchAddress("eventNumber", &EventNumber);
  for(int i = 0; i < Chain.GetEntries(); i++) {
    Chain.GetEntry(i);
    if(Bu_constD0PV_M < 5249.34 || Bu_constD0PV_M > 5309.34) {
      continue;
    }
    auto Search = m_EventNumbers.find(EventNumber);
    if(Search == m_EventNumbers.end()) {
      m_EventNumbers.insert({EventNumber, 1});
    } else {
      Search->second++;
    }
  }
}

void EventNumbers::CompareEvents(const EventNumbers &rhs) const {
  std::cout << "First dataset contains " << this->m_EventNumbers.size() << " events in the signal region\n";
  std::cout << "Second dataset contains " << rhs.m_EventNumbers.size() << " events in the signal region\n";
  int NumberOverlap = 0;
  for(auto iter = rhs.m_EventNumbers.begin(); iter != rhs.m_EventNumbers.end(); iter++) {
    if(this->m_EventNumbers.find(iter->first) != this->m_EventNumbers.end()) {
      NumberOverlap++;
    }
  }
  std::cout << "They have " << NumberOverlap << " event numbers in common\n";
}

void EventNumbers::CountMultipleCandidates() const {
  int MultipleCandidates = 0;
  for(auto iter = m_EventNumbers.begin(); iter != m_EventNumbers.end(); iter++) {
    if(iter->second > 1) {
      std::cout << "Event number " << iter->first << " has " << iter->second << " candidates\n";
      MultipleCandidates++;
    }
  }
  std::cout << MultipleCandidates << " multiple candidates found\n";
}
