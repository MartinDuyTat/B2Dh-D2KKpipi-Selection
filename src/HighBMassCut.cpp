// Martin Duy Tat 25th February 2021

#include"HighBMassCut.h"
#include"BaseCuts.h"

HighBMassCuts::HighBMassCuts(bool BachelorCuts, bool KaonDaughterCuts, bool DecayTreeFitCuts, bool DMassCut, bool LoosePIDCuts): BaseCuts(BachelorCuts, KaonDaughterCuts, DecayTreeFitCuts, DMassCut, LoosePIDCuts, false) {
}

TCut HighBMassCuts::BMassCut() const {
  return TCut("Bu_constD0PV_M > 5800 && Bu_constD0PV_M < 7000");
}

TCut HighBMassCuts::ApplyCuts() const {
  return BMassCut() && BaseCuts::ApplyCuts();
}
