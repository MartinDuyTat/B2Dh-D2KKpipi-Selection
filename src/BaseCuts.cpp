// Martin Duy Tat 25th February 2021

#include<string>
#include<stdexcept>
#include"BaseCuts.h"
#include"TCut.h"

BaseCuts::BaseCuts(const std::string &DDecayMode, int Year, bool BachelorCuts, bool KaonDaughterCuts, bool DecayTreeFitCut, bool DMassCut, bool LoosePIDCuts, bool TriggerCuts, bool BMassCut): m_DDecayMode(DDecayMode), m_Year(Year), m_BachelorCuts(BachelorCuts), m_KaonDaughterCuts(KaonDaughterCuts), m_DecayTreeFitCut(DecayTreeFitCut), m_DMassCut(DMassCut), m_LoosePIDCuts(LoosePIDCuts), m_TriggerCuts(TriggerCuts), m_BMassCut(BMassCut), m_BMassName("Bu_constD0PV_M"), m_DMassName("D0_M"), m_DTFStatusName("Bu_constD0PV_status") {
}

BaseCuts::~BaseCuts() {
}

TCut BaseCuts::BachelorCuts() const {
  return TCut("Bach_P < 100000 && Bach_hasRich == 1 && Bach_isMuon == 0");
}

TCut BaseCuts::KaonDaughterCuts() const {
  return TCut("h1_P < 100000 && h1_hasRich == 1 && h2_P < 100000 && h2_hasRich == 1");
}

TCut BaseCuts::DecayTreeFitCut() const {
  std::string Cut = m_DTFStatusName + std::string(" == 0");
  return TCut(Cut.c_str());
}

TCut BaseCuts::DMassCut() const {
  std::string Cut = m_DMassName + std::string(" > 1839.84 && ") + m_DMassName + std::string(" < 1889.84");
  return TCut(Cut.c_str());
}

TCut BaseCuts::LoosePIDCuts() const {
  if(m_DDecayMode == "KKpipi") {
    return TCut("h1_PIDK > -10 && h2_PIDK > -10 && h3_PIDK < 20 && h4_PIDK < 20");
  } else if(m_DDecayMode == "pipipipi") {
    return TCut("h1_PIDK < 20 && h2_PIDK < 20 && h3_PIDK < 20 && h4_PIDK < 20");
  } else {
    return TCut();
  }
}

TCut BaseCuts::TriggerCuts() const {
  TCut TriggerCut;
  if(m_Year <= 2012) {
    TriggerCut = TCut("(Bu_L0Global_TIS == 1 || Bu_L0HadronDecision_TOS == 1) && "
                      "(Bu_Hlt1TrackAllL0Decision_TOS == 1)");
    if(m_DDecayMode == "KKpipi") {
      TriggerCut = TriggerCut && TCut("(Bu_Hlt2Topo2BodyBBDTDecision_TOS == 1 || "
				      " Bu_Hlt2Topo3BodyBBDTDecision_TOS == 1 || "
				      " Bu_Hlt2Topo4BodyBBDTDecision_TOS == 1 || "
				      " Bu_Hlt2IncPhiDecision_TOS == 1)");
    } else {
      TriggerCut = TriggerCut && TCut("(Bu_Hlt2Topo2BodyBBDTDecision_TOS == 1 || "
				      " Bu_Hlt2Topo3BodyBBDTDecision_TOS == 1 || "
				      " Bu_Hlt2Topo4BodyBBDTDecision_TOS == 1)");
    }
    return TriggerCut;
  } else if (m_Year >= 2015 && m_Year <= 2018) {
    TriggerCut = TCut("(Bu_L0Global_TIS == 1 || Bu_L0HadronDecision_TOS == 1) && "
                      "(Bu_Hlt1TrackMVADecision_TOS == 1 || Bu_Hlt1TwoTrackMVADecision_TOS == 1)");
    if(m_DDecayMode == "KKpipi") {
      TriggerCut = TriggerCut && TCut("(Bu_Hlt2Topo2BodyDecision_TOS == 1 ||"
				      " Bu_Hlt2Topo3BodyDecision_TOS == 1 ||"
				      " Bu_Hlt2Topo4BodyDecision_TOS == 1 ||"
				      " Bu_Hlt2IncPhiDecision_TOS == 1)");
    } else {
      TriggerCut = TriggerCut && TCut("(Bu_Hlt2Topo2BodyDecision_TOS == 1 ||"
				      " Bu_Hlt2Topo3BodyDecision_TOS == 1 ||"
				      " Bu_Hlt2Topo4BodyDecision_TOS == 1)");
    }
    return TriggerCut;
  } else {
    return TCut();
  }
}

TCut BaseCuts::BMassCut() const {
  std::string Cut = m_BMassName + std::string(" > 5080 && ") + m_BMassName + std::string(" < 5800");
  return TCut(Cut.c_str());
}

TCut BaseCuts::FlightSignificanceCut() const {
  return TCut("(D0_ENDVERTEX_Z - Bu_ENDVERTEX_Z)/(sqrt(D0_ENDVERTEX_ZERR*D0_ENDVERTEX_ZERR + Bu_ENDVERTEX_ZERR*Bu_ENDVERTEX_ZERR)) > 2.0");
}

TCut BaseCuts::KSVetoCut() const {
  if(m_DDecayMode == "pipipipi") {
    std::string m13("sqrt((Bu_constD0PV_D0_h1_PE + Bu_constD0PV_D0_h3_PE)^2 - (Bu_constD0PV_D0_h1_PX + Bu_constD0PV_D0_h3_PX)^2 - (Bu_constD0PV_D0_h1_PY + Bu_constD0PV_D0_h3_PY)^2 - (Bu_constD0PV_D0_h1_PZ + Bu_constD0PV_D0_h3_PZ)^2)");
    std::string m14("sqrt((Bu_constD0PV_D0_h1_PE + Bu_constD0PV_D0_h4_PE)^2 - (Bu_constD0PV_D0_h1_PX + Bu_constD0PV_D0_h4_PX)^2 - (Bu_constD0PV_D0_h1_PY + Bu_constD0PV_D0_h4_PY)^2 - (Bu_constD0PV_D0_h1_PZ + Bu_constD0PV_D0_h4_PZ)^2)");
    std::string m23("sqrt((Bu_constD0PV_D0_h2_PE + Bu_constD0PV_D0_h3_PE)^2 - (Bu_constD0PV_D0_h2_PX + Bu_constD0PV_D0_h3_PX)^2 - (Bu_constD0PV_D0_h2_PY + Bu_constD0PV_D0_h3_PY)^2 - (Bu_constD0PV_D0_h2_PZ + Bu_constD0PV_D0_h3_PZ)^2)");
    std::string m24("sqrt((Bu_constD0PV_D0_h2_PE + Bu_constD0PV_D0_h4_PE)^2 - (Bu_constD0PV_D0_h2_PX + Bu_constD0PV_D0_h4_PX)^2 - (Bu_constD0PV_D0_h2_PY + Bu_constD0PV_D0_h4_PY)^2 - (Bu_constD0PV_D0_h2_PZ + Bu_constD0PV_D0_h4_PZ)^2)");
    TCut KSVeto13((m13 + " < 480 || " + m13 + " > 505").c_str());
    TCut KSVeto14((m14 + " < 480 || " + m14 + " > 505").c_str());
    TCut KSVeto23((m23 + " < 480 || " + m23 + " > 505").c_str());
    TCut KSVeto24((m24 + " < 480 || " + m24 + " > 505").c_str());
    return KSVeto13 && KSVeto14 && KSVeto23 && KSVeto24;
  } else if(m_DDecayMode == "KKpipi") {
    // This is really annoying but the particle ordering changes from event to event in Run 1...
    std::string m13("sqrt((Bu_constD0PV_D0_h3_PE + Bu_constD0PV_D0_h1_PE)^2 - (Bu_constD0PV_D0_h3_PX + Bu_constD0PV_D0_h1_PX)^2 - (Bu_constD0PV_D0_h3_PY + Bu_constD0PV_D0_h1_PY)^2 - (Bu_constD0PV_D0_h3_PZ + Bu_constD0PV_D0_h1_PZ)^2)");
    TCut KSVeto13(("Bu_constD0PV_D0_h3_ID*Bu_constD0PV_D0_h1_ID == -44521 && (" + m13 + " < 477 || " + m13 + " > 507)").c_str());
    std::string m14("sqrt((Bu_constD0PV_D0_h4_PE + Bu_constD0PV_D0_h1_PE)^2 - (Bu_constD0PV_D0_h4_PX + Bu_constD0PV_D0_h1_PX)^2 - (Bu_constD0PV_D0_h4_PY + Bu_constD0PV_D0_h1_PY)^2 - (Bu_constD0PV_D0_h4_PZ + Bu_constD0PV_D0_h1_PZ)^2)");
    TCut KSVeto14(("Bu_constD0PV_D0_h4_ID*Bu_constD0PV_D0_h1_ID == -44521 && (" + m14 + " < 477 || " + m14 + " > 507)").c_str());
    std::string m24("sqrt((Bu_constD0PV_D0_h4_PE + Bu_constD0PV_D0_h2_PE)^2 - (Bu_constD0PV_D0_h4_PX + Bu_constD0PV_D0_h2_PX)^2 - (Bu_constD0PV_D0_h4_PY + Bu_constD0PV_D0_h2_PY)^2 - (Bu_constD0PV_D0_h4_PZ + Bu_constD0PV_D0_h2_PZ)^2)");
    TCut KSVeto24(("Bu_constD0PV_D0_h4_ID*Bu_constD0PV_D0_h2_ID == -44521 && (" + m24 + " < 477 || " + m24 + " > 507)").c_str());
    std::string m23("sqrt((Bu_constD0PV_D0_h3_PE + Bu_constD0PV_D0_h2_PE)^2 - (Bu_constD0PV_D0_h3_PX + Bu_constD0PV_D0_h2_PX)^2 - (Bu_constD0PV_D0_h3_PY + Bu_constD0PV_D0_h2_PY)^2 - (Bu_constD0PV_D0_h3_PZ + Bu_constD0PV_D0_h2_PZ)^2)");
    TCut KSVeto23(("Bu_constD0PV_D0_h3_ID*Bu_constD0PV_D0_h2_ID == -44521 && (" + m23 + " < 477 || " + m23 + " > 507)").c_str());
    return KSVeto13 || KSVeto14 || KSVeto24 || KSVeto23;
  } else {
    // Probably need to add Kpipipi in case someone needs to redo the background studies
    throw std::invalid_argument("D mode " + m_DDecayMode + " not a valid decay");
  }
}

TCut BaseCuts::GetCuts() const {
  TCut Cuts;
  if(m_BachelorCuts) {
    Cuts = Cuts && BachelorCuts();
  }
  if(m_KaonDaughterCuts) {
    Cuts = Cuts && KaonDaughterCuts();
  }
  if(m_DecayTreeFitCut) {
    Cuts = Cuts && DecayTreeFitCut();
  }
  if(m_DMassCut) {
    Cuts = Cuts && DMassCut();
  }
  if(m_LoosePIDCuts) {
    Cuts = Cuts && LoosePIDCuts();
  }
  if(m_TriggerCuts) {
    Cuts = Cuts && TriggerCuts();
  }
  if(m_BMassCut) {
    Cuts = Cuts && BMassCut();
  }
  return Cuts && FlightSignificanceCut() && KSVetoCut();
}

void BaseCuts::SetBMassName(const std::string &BMassName) {
  m_BMassName = BMassName;
}

void BaseCuts::SetDMassName(const std::string &DMassName) {
  m_DMassName = DMassName;
}

void BaseCuts::SetDTFStatusName(const std::string &DTFStatusName) {
  m_DTFStatusName = DTFStatusName;
}
