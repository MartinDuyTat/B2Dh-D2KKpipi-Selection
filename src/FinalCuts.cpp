// Martin Duy Tat 8th March 2021

#include<string>
#include"FinalCuts.h"
#include"TCut.h"

FinalCuts::FinalCuts(const std::string &BMode, const std::string &DMode, double BDTcut, bool BachelorPIDCut, bool KaonDaughterPIDCut, bool FlightSignificanceCut, bool DTFChi2Cut, bool KSVeto): m_BMode(BMode), m_DMode(DMode), m_BDTcut(BDTcut), m_BachelorPIDCut(BachelorPIDCut), m_KaonDaughterPIDCut(KaonDaughterPIDCut), m_FlightSignificanceCut(FlightSignificanceCut), m_DTFChi2Cut(DTFChi2Cut), m_KSVeto(KSVeto) {
}

FinalCuts::~FinalCuts() {
}

TCut FinalCuts::BDTCut() const {
  return TCut(std::string("BDToutput > " + std::to_string(m_BDTcut)).c_str());
}

TCut FinalCuts::BachelorPIDCut() const {
  if(m_BMode == "pi") {
    return TCut("Bach_PIDK < 4 && Bach_isMuon == 0");
  } else if(m_BMode == "K") {
    return TCut("Bach_PIDK > 4 && Bach_isMuon == 0");
  } else {
    return TCut();
  }
}

TCut FinalCuts::KaonDaughterPIDCut() const {
  return TCut("h2_PIDK > 0");
}

TCut FinalCuts::FlightSignificanceCut() const {
  return TCut("(D0_ENDVERTEX_Z - Bu_ENDVERTEX_Z)/(sqrt(D0_ENDVERTEX_ZERR*D0_ENDVERTEX_ZERR + Bu_ENDVERTEX_ZERR*Bu_ENDVERTEX_ZERR)) > 2.0");
}

TCut FinalCuts::DTFChi2Cut() const {
  return TCut("log(Bu_constD0PV_chi2) < 3");
}

TCut FinalCuts::KSVetoCut() const {
  std::string m13("sqrt((Bu_constD0PV_D0_h1_PE + Bu_constD0PV_D0_h3_PE)^2 - (Bu_constD0PV_D0_h1_PX + Bu_constD0PV_D0_h3_PX)^2 - (Bu_constD0PV_D0_h1_PY + Bu_constD0PV_D0_h3_PY)^2 - (Bu_constD0PV_D0_h1_PZ + Bu_constD0PV_D0_h3_PZ)^2)");
  std::string m14("sqrt((Bu_constD0PV_D0_h1_PE + Bu_constD0PV_D0_h4_PE)^2 - (Bu_constD0PV_D0_h1_PX + Bu_constD0PV_D0_h4_PX)^2 - (Bu_constD0PV_D0_h1_PY + Bu_constD0PV_D0_h4_PY)^2 - (Bu_constD0PV_D0_h1_PZ + Bu_constD0PV_D0_h4_PZ)^2)");
  std::string m23("sqrt((Bu_constD0PV_D0_h2_PE + Bu_constD0PV_D0_h3_PE)^2 - (Bu_constD0PV_D0_h2_PX + Bu_constD0PV_D0_h3_PX)^2 - (Bu_constD0PV_D0_h2_PY + Bu_constD0PV_D0_h3_PY)^2 - (Bu_constD0PV_D0_h2_PZ + Bu_constD0PV_D0_h3_PZ)^2)");
  std::string m24("sqrt((Bu_constD0PV_D0_h2_PE + Bu_constD0PV_D0_h4_PE)^2 - (Bu_constD0PV_D0_h2_PX + Bu_constD0PV_D0_h4_PX)^2 - (Bu_constD0PV_D0_h2_PY + Bu_constD0PV_D0_h4_PY)^2 - (Bu_constD0PV_D0_h2_PZ + Bu_constD0PV_D0_h4_PZ)^2)");
  TCut KSVeto13((m13 + " < 480 || " + m13 + " > 505").c_str());
  TCut KSVeto14((m14 + " < 480 || " + m14 + " > 505").c_str());
  TCut KSVeto23((m23 + " < 480 || " + m23 + " > 505").c_str());
  TCut KSVeto24((m24 + " < 480 || " + m24 + " > 505").c_str());
  return KSVeto13 && KSVeto14 && KSVeto23 && KSVeto24;
}

TCut FinalCuts::GetCuts() const {
  TCut Cuts = BDTCut();
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
  if(m_KSVeto) {
    Cuts = Cuts && KSVetoCut();
  }
  return Cuts;
}
