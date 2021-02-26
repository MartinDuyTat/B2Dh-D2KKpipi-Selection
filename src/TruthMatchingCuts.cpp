// Martin Duy Tat 26th February 2021

#include<string>
#include"TCut.h"
#include"TruthMatchingCuts.h"

TruthMatchingCuts::TruthMatchingCuts(std::string DecayMode, int Year, bool BachelorCuts, bool KaonDaughterCuts, bool DecayTreeFitCuts, bool DMassCut, bool LoosePIDCuts, BMassCuts): BaseCuts(Year, BachelorCuts, KaonDaughterCuts, DecayTreeFitCuts, DMassCut, LoosePIDCuts, BMassCuts), m_DecayMode(DecayMode) {
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
  TCut h4Truth("(abs(h4_TRUEID)          == 0 || abs(h4_TRUEID)          == 211) && "
               "(abs(h4_MC_MOTHER_ID)    == 0 || abs(h4_MC_MOTHER_ID)    == 421) && " 
               "(abs(h4_MC_GD_MOTHER_ID) == 0 || abs(h4_MC_GD_MOTHER_ID) == 521)");
  TCut BachTruth;
  if(m_DecayMode == "Pi") {
    BachTruth = BachTruth && TCut("(abs(Bach_TRUEID)          == 0 || abs(Bach_TRUEID)          == 211) && "
                                  "(abs(Bach_MC_MOTHER_ID)    == 0 || abs(Bach_MC_MOTHER_ID)    == 521)";
  } else if(m_DecayMode "K") {
    BachTruth = BachTruth && TCut("(abs(Bach_TRUEID)          == 0 || abs(Bach_TRUEID)          == 321) && "
                                  "(abs(Bach_MC_MOTHER_ID)    == 0 || abs(Bach_MC_MOTHER_ID)    == 521)";
  } else {
    BachTruth = BachTruth && TCut("0");
  }
  return CategoryTruth && D0Truth && h1Truth && h2Truth && h3Truth && h4Truth && BachTruth;
}
