// Martin Duy Tat 26th February 2021

#include<string>
#include"TCut.h"
#include"TruthMatchingCuts.h"

TruthMatchingCuts::TruthMatchingCuts(const std::string &DecayMode, int Year, const std::string &MisID, bool BachelorCuts, bool KaonDaughterCuts, bool DecayTreeFitCuts, bool DMassCut, bool LoosePIDCuts, bool BMassCuts): BaseCuts(Year, BachelorCuts, KaonDaughterCuts, DecayTreeFitCuts, DMassCut, LoosePIDCuts, BMassCuts), m_DecayMode(DecayMode), m_MisID(MisID) {
}

TruthMatchingCuts::~TruthMatchingCuts() {
}

TCut TruthMatchingCuts::GetTruthMatchingCuts() const {
  TCut CategoryTruth("Bu_BKGCAT == 0 || Bu_BKGCAT == 50 || Bu_BKGCAT == 60");
  TCut D0Truth("(abs(D0_TRUEID)          == 0 || abs(D0_TRUEID)          == 421) && "
               "(abs(D0_MC_MOTHER_ID)    == 0 || abs(D0_MC_MOTHER_ID)    == 521)");
  TCut h1Truth("(abs(h1_TRUEID)          == 0 || abs(h1_TRUEID)          == 321) && "
               "(abs(h1_MC_MOTHER_ID)    == 0 || abs(h1_MC_MOTHER_ID)    == 421) && " 
               "(abs(h1_MC_GD_MOTHER_ID) == 0 || abs(h1_MC_GD_MOTHER_ID) == 521)");
  TCut h2Truth("(abs(h2_TRUEID)          == 0 || abs(h2_TRUEID)          == 321) && "
               "(abs(h2_MC_MOTHER_ID)    == 0 || abs(h2_MC_MOTHER_ID)    == 421) && " 
               "(abs(h2_MC_GD_MOTHER_ID) == 0 || abs(h2_MC_GD_MOTHER_ID) == 521)");
  TCut h3Truth("(abs(h3_TRUEID)          == 0 || abs(h3_TRUEID)          == 211) && "
               "(abs(h3_MC_MOTHER_ID)    == 0 || abs(h3_MC_MOTHER_ID)    == 421) && " 
               "(abs(h3_MC_GD_MOTHER_ID) == 0 || abs(h3_MC_GD_MOTHER_ID) == 521)");
  if(m_MisID == "Single") {
    h1Truth = TCut("(abs(h1_TRUEID)          == 321) && "
		   "(abs(h1_MC_MOTHER_ID)    == 0 || abs(h1_MC_MOTHER_ID)    == 421) && " 
		   "(abs(h1_MC_GD_MOTHER_ID) == 0 || abs(h1_MC_GD_MOTHER_ID) == 521)");
    h2Truth = TCut("(abs(h2_TRUEID)          == 0 || abs(h2_TRUEID)          == 211) && "
		   "(abs(h2_MC_MOTHER_ID)    == 0 || abs(h2_MC_MOTHER_ID)    == 421) && " 
		   "(abs(h2_MC_GD_MOTHER_ID) == 0 || abs(h2_MC_GD_MOTHER_ID) == 521)");
    h3Truth = TCut("(abs(h3_MC_MOTHER_ID)    == 0 || abs(h3_MC_MOTHER_ID)    == 421) && " 
		   "(abs(h3_MC_GD_MOTHER_ID) == 0 || abs(h3_MC_GD_MOTHER_ID) == 521)");
  } else if(m_MisID == "Triple") {
    h1Truth = TCut("(abs(h1_TRUEID)          == 211) && "
		   "(abs(h1_MC_MOTHER_ID)    == 0 || abs(h1_MC_MOTHER_ID)    == 421) && " 
		   "(abs(h1_MC_GD_MOTHER_ID) == 0 || abs(h1_MC_GD_MOTHER_ID) == 521)");
    h2Truth = TCut("(abs(h2_TRUEID)          == 0 || abs(h2_TRUEID)          == 211) && "
		   "(abs(h2_MC_MOTHER_ID)    == 0 || abs(h2_MC_MOTHER_ID)    == 421) && " 
		   "(abs(h2_MC_GD_MOTHER_ID) == 0 || abs(h2_MC_GD_MOTHER_ID) == 521)");
    h3Truth = TCut("(abs(h3_MC_MOTHER_ID)    == 0 || abs(h3_MC_MOTHER_ID)    == 421) && " 
		   "(abs(h3_MC_GD_MOTHER_ID) == 0 || abs(h3_MC_GD_MOTHER_ID) == 521)");
  }
  TCut h4Truth("(abs(h4_TRUEID)          == 0 || abs(h4_TRUEID)          == 211) && "
               "(abs(h4_MC_MOTHER_ID)    == 0 || abs(h4_MC_MOTHER_ID)    == 421) && " 
               "(abs(h4_MC_GD_MOTHER_ID) == 0 || abs(h4_MC_GD_MOTHER_ID) == 521)");
  TCut BachTruth;
  if(m_DecayMode == "pi") {
    BachTruth = BachTruth && TCut("(abs(Bach_TRUEID)          == 0 || abs(Bach_TRUEID)          == 211) && "
                                  "(abs(Bach_MC_MOTHER_ID)    == 0 || abs(Bach_MC_MOTHER_ID)    == 521)");
  } else if(m_DecayMode == "K") {
    BachTruth = BachTruth && TCut("(abs(Bach_TRUEID)          == 0 || abs(Bach_TRUEID)          == 321) && "
                                  "(abs(Bach_MC_MOTHER_ID)    == 0 || abs(Bach_MC_MOTHER_ID)    == 521)");
  } else {
    BachTruth = BachTruth && TCut("0");
  }
  return CategoryTruth && D0Truth && h1Truth && h2Truth && h3Truth && h4Truth && BachTruth;
}

TCut TruthMatchingCuts::GetCuts() const {
  return BaseCuts::GetCuts() && GetTruthMatchingCuts();
}
