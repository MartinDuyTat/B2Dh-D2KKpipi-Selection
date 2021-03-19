// Martin Duy Tat 25th February 2021

#include"TCut.h"
#include"CharmlessCuts.h"
#include"BaseCuts.h"

CharmlessCuts::CharmlessCuts(int Year, bool BachelorCuts, bool KaonDaughterCuts, bool LoosePIDCuts, bool BMassCut): BaseCuts(Year, BachelorCuts, KaonDaughterCuts, false, false, LoosePIDCuts, BMassCut) {
}

CharmlessCuts::~CharmlessCuts() {
}

TCut CharmlessCuts::DMassCut() const {
  return TCut("D0_M > 1770 && D0_M < 1820");
}

TCut CharmlessCuts::GetCuts() const {
  return DMassCut() && BaseCuts::GetCuts();
}
