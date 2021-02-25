// Martin Duy Tat 25th February 2021

#include"BaseCuts.h"
#include"TCut.h"

BaseCuts::BaseCuts(bool BachelorCuts, bool KaonDaughterCuts, bool DecayTreeFitCuts, bool DMassCut, bool LoosePIDCuts, bool TriggerCuts, bool BMassCut): m_Year(Year), m_BachelorCuts(BachelorCuts), m_KaonDaughterCuts(KaonDaughterCuts), m_DecayTreeFitCuts(DecayTreeFitCuts), m_DMassCut(DMassCut), m_LoosePIDCuts(LoosePIDCuts), m_TriggerCuts(TriggerCuts), m_BMassCuts(BMassCuts) {
}

TCut BaseCuts::BachelorCuts() const {
  return TCut("Bach_P < 100000 && Bach_hasRich == 1");
}

TCut BaseCuts::KaonDaughterCuts() const {
  return TCut("h1_P < 100000 && h1_hasRich == 1 && h2_P < 100000 && h2_hasRich == 1");
}

TCut BaseCuts::DecayTreeFitCut() const {
  return TCut("Bu_constD0PV_status == 0");
}

TCut BaseCuts::DMassCut() const {
  return TCut("abs(D0_DM) < 25");
}

TCut BaseCuts::LoosePIDCuts() const {
  return TCut("h1_PIDK > -5 && h2_PIDK > -5 && h3_PIDK < 20 && h4_PIDK < 20");
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
  return TCut("Bu_constD0PV_M > 5080 && Bu_constD0PV_M < 7000");
}

TCut BaseCuts::ApplyBaseCuts() const {
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
  if(m_BMassCuts) {
    Cuts = Cuts && BMassCut();
  }
  return Cuts;
}
