// Martin Duy Tat 25th February 2021

#include<string>
#include"TCut.h"
#include"CombinatorialBMassCut.h"
#include"BaseCuts.h"

CombinatorialBMassCut::CombinatorialBMassCut(const std::string &DDecayMode, int Year, bool BachelorCuts, bool KaonDaughterCuts, bool DecayTreeFitCuts, bool DMassCut, bool LoosePIDCuts): BaseCuts(DDecayMode, Year, BachelorCuts, KaonDaughterCuts, DecayTreeFitCuts, DMassCut, LoosePIDCuts, false) {
}

CombinatorialBMassCut::~CombinatorialBMassCut() {
}

TCut CombinatorialBMassCut::BMassCut() const {
  return TCut("Bu_constD0PV_M > 5600 && Bu_constD0PV_M < 6500");
}

TCut CombinatorialBMassCut::GetCuts() const {
  return BMassCut() && BaseCuts::GetCuts();
}
