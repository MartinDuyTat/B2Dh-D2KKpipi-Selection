// Martin Duy Tat 19th March 2021

#include<string>
#include"TCut.h"
#include"CharmlessCuts.h"
#include"BaseCuts.h"

CharmlessCuts::CharmlessCuts(const std::string &DDecayMode, int Year, bool BachelorCuts, bool KaonDaughterCuts, bool LoosePIDCuts, bool TriggerCuts, bool BMassCut): BaseCuts(DDecayMode, Year, BachelorCuts, KaonDaughterCuts, false, false, LoosePIDCuts, TriggerCuts, false), m_BMassCut(BMassCut) {
}

CharmlessCuts::~CharmlessCuts() {
}

TCut CharmlessCuts::DMassCut() const {
  return TCut("(D0_M > 1770 && D0_M < 1820) || (D0_M > 1910 && D0_M < 1960)");
}

TCut CharmlessCuts::BMassCut() const {
  return TCut("Bu_M > 5080 && Bu_M < 5800");
}

TCut CharmlessCuts::GetCuts() const {
  TCut Cuts = DMassCut() && BaseCuts::GetCuts();
  if(m_BMassCut) {
    return Cuts && BMassCut();
  } else {
    return Cuts;
  }
}
