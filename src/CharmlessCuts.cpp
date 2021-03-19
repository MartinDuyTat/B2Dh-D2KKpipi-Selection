// Martin Duy Tat 19th March 2021

#include"TCut.h"
#include"CharmlessCuts.h"
#include"BaseCuts.h"

CharmlessCuts::CharmlessCuts(int Year, bool BachelorCuts, bool KaonDaughterCuts, bool LoosePIDCuts, bool BMassCut): BaseCuts(Year, BachelorCuts, KaonDaughterCuts, false, false, LoosePIDCuts, false), m_BMassCut(BMassCut) {
}

CharmlessCuts::~CharmlessCuts() {
}

TCut CharmlessCuts::DMassCut() const {
  return TCut("D0_M > 1770 && D0_M < 1820");
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
