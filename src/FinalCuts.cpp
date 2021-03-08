// Martin Duy Tat 8th March 2021

#include<string>
#include"FinalCuts.h"
#include"TCut.h"

FinalCuts::FinalCuts(std::string Mode, bool BachelorPIDCut, bool KaonDaughterPIDCut, bool FlightSignificanceCut, bool DTFChi2Cut): m_Mode(Mode), m_BachelorPIDCut(BachelorPIDCut), m_KaonDaughterPIDCut(KaonDaughterPIDCut), m_FlightSignificanceCut(FlightSignificanceCut), m_DTFChi2Cut(DTFChi2Cut) {
}

FinalCuts::~FinalCuts() {
}

TCut FinalCuts::BachelorPIDCut() const {
  if(m_Mode == "pi") {
    return TCut("Bach_PIDK < 4");
  } else if(m_Mode == "K") {
    return TCut("Bach_PIDK > 4");
  } else {
    return TCut();
  }
}

TCut FinalCuts::KaonDaughterPIDCut() const {
  return TCut("h1_PIDK > -5 && h2_PIDK > -5");
}

TCut FinalCuts::FlightSignificanceCut() const {
  return TCut("(D0_ENDVERTEX_Z - Bu_ENDVERTEX_Z)/( sqrt( D0_ENDVERTEX_ZERR*D0_ENDVERTEX_ZERR + Bu_ENDVERTEX_ZERR*Bu_ENDVERTEX_ZERR)) > 0.5");
}

TCut FinalCuts::DTFChi2Cut() const {
  return TCut("log(Bu_constD0PV_chi2) < 3");
}

TCut FinalCuts::GetCuts() const {
  TCut Cuts;
  if(m_BachelorPIDCut) {
    Cuts = Cuts && BachelorPIDCut();
  }
  if(m_KaonDaughterPIDCut) {
    Cuts = Cuts && KaonDaughterPIDCut();
  }
  if(m_FlightSignificanceCut) {
    Cuts = Cuts && FlightSignificanceCut();
  }
  if(m_DTFChi2Cut) {
    Cuts = Cuts && DTFChi2Cut();
  }
  return Cuts;
}
