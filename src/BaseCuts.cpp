// Martin Duy Tat 25th February 2021

#include<string>
#include"BaseCuts.h"
#include"TCut.h"

BaseCuts::BaseCuts(int Year, bool BachelorCuts, bool KaonDaughterCuts, bool DecayTreeFitCut, bool DMassCut, bool LoosePIDCuts, bool TriggerCuts, bool BMassCut): m_Year(Year), m_BachelorCuts(BachelorCuts), m_KaonDaughterCuts(KaonDaughterCuts), m_DecayTreeFitCut(DecayTreeFitCut), m_DMassCut(DMassCut), m_LoosePIDCuts(LoosePIDCuts), m_TriggerCuts(TriggerCuts), m_BMassCut(BMassCut), m_BMassName("Bu_constD0PV_M"), m_DMassName("D0_M"), m_DTFStatusName("Bu_constD0PV_status") {
}

BaseCuts::~BaseCuts() {
}

TCut BaseCuts::BachelorCuts() const {
  return TCut("Bach_P < 100000 && Bach_hasRich == 1");
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
  return TCut("h1_PIDK > -10 && h2_PIDK > -10 && h3_PIDK < 20 && h4_PIDK < 20");
}

TCut BaseCuts::TriggerCuts() const {
  if(m_Year <= 2012) {
    return TCut("(Bu_L0Global_TIS == 1 || Bu_L0HadronDecision_TOS == 1) && "
                "(Bu_Hlt1TrackAllL0Decision_TOS == 1 ) && "
	        "(Bu_Hlt2Topo2BodyBBDTDecision_TOS == 1 || Bu_Hlt2Topo3BodyBBDTDecision_TOS == 1 || Bu_Hlt2Topo4BodyBBDTDecision_TOS == 1)");
  } else if (m_Year >= 2015 && m_Year <= 2018) {
    return TCut("(Bu_L0Global_TIS == 1 || Bu_L0HadronDecision_TOS == 1) && "
                "(Bu_Hlt1TrackMVADecision_TOS == 1 || Bu_Hlt1TwoTrackMVADecision_TOS == 1) && "
	        "(Bu_Hlt2Topo2BodyDecision_TOS == 1 || Bu_Hlt2Topo3BodyDecision_TOS == 1 || Bu_Hlt2Topo4BodyDecision_TOS == 1)");
  } else {
    return TCut();
  }
}

TCut BaseCuts::BMassCut() const {
  std::string Cut = m_BMassName + std::string(" > 5080 && ") + m_BMassName + std::string(" < 5800");
  return TCut(Cut.c_str());
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
  return Cuts;
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
