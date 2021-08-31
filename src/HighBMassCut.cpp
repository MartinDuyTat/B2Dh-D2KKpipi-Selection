// Martin Duy Tat 25th February 2021

#include<string>
#include"TCut.h"
#include"HighBMassCut.h"
#include"BaseCuts.h"

HighBMassCut::HighBMassCut(const std::string &DDecayMode, int Year, bool BachelorCuts, bool KaonDaughterCuts, bool DecayTreeFitCuts, bool DMassCut, bool LoosePIDCuts): BaseCuts(DDecayMode, Year, BachelorCuts, KaonDaughterCuts, DecayTreeFitCuts, DMassCut, LoosePIDCuts, false) {
}

HighBMassCut::~HighBMassCut() {
}

TCut HighBMassCut::BMassCut() const {
  return TCut("Bu_constD0PV_M > 5800 && Bu_constD0PV_M < 7000");
}

TCut HighBMassCut::GetCuts() const {
  return BMassCut() && BaseCuts::GetCuts();
}
