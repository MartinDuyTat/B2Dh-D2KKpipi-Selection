// Martin Duy Tat 11th June 2021

#include<string>
#include<fstream>
#include<iostream>
#include<algorithm>
#include"EventNumbers.h"
#include"TChain.h"

EventNumbers::EventNumbers(const std::string &Filename, double BDTCut) {
  std::ifstream Infile(Filename);
  std::string line;
  TChain Chain("DecayTree");
  while(std::getline(Infile, line)) {
    Chain.Add(line.c_str());
  }
  double BDToutput;
  Float_t Bu_constD0PV_M;
  ULong64_t EventNumber;
  Chain.SetBranchStatus("*", 0);
  Chain.SetBranchStatus("eventNumber", 1);
  Chain.SetBranchStatus("Bu_constD0PV_M", 1);
  Chain.SetBranchAddress("Bu_constD0PV_M", &Bu_constD0PV_M);
  Chain.SetBranchAddress("eventNumber", &EventNumber);
  Chain.SetBranchAddress("BDToutput", &BDToutput);
  for(int i = 0; i < Chain.GetEntries(); i++) {
    Chain.GetEntry(i);
    if(Bu_constD0PV_M < 5249.34 || Bu_constD0PV_M > 5309.34) {
      continue;
    }
    if(BDToutput < BDTCut) {
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
  std::map<ULong64_t, int> Intersection, Union;
  std::set_intersection(this->m_EventNumbers.begin(), this->m_EventNumbers.end(), rhs.m_EventNumbers.begin(), rhs.m_EventNumbers.end(), std::inserter(Intersection, Intersection.begin()), [](const auto &a, const auto &b) {return a.first < b.first;});
  int NumberIntersection = Intersection.size();
  std::cout << "They have " << NumberIntersection << " event numbers in the intersection\n";
  std::set_union(this->m_EventNumbers.begin(), this->m_EventNumbers.end(), rhs.m_EventNumbers.begin(), rhs.m_EventNumbers.end(), std::inserter(Union, Union.begin()), [](const auto &a, const auto &b) {return a.first < b.first;});
  int NumberUnion = Union.size();
  std::cout << "They have " << NumberUnion << " event numbers in the union\n";
}

void EventNumbers::CountMultipleCandidates() const {
  int MultipleCandidates = 0;
  for(auto iter = m_EventNumbers.begin(); iter != m_EventNumbers.end(); iter++) {
    if(iter->second > 1) {
      MultipleCandidates++;
    }
  }
  std::cout << MultipleCandidates << " multiple candidates found\n";
}
