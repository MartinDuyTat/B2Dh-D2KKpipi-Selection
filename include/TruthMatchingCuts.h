// Martin Duy Tat 26th Februrary 2021
/**
 * TruthMatchingCuts is a class derived from BaseCuts and adds cuts for truth matching in MC samples
 * Mainly used for selection of candidates in the signal training sample
 */

#ifndef TRUTHMATCHINGCUTS
#define TRUTHMATCHINGCUTS

#include<string>
#include"BaseCuts.h"
#include"TCut.h"

class TruthMatchingCuts: public BaseCuts {
  public:
    /**
     * Constructor that sets the same options as BaseCuts
     */
    TruthMatchingCuts(std::string DecayMode, bool BachelorCuts = true, bool KaonDaughterCuts = true, bool DecayTreeFitCuts = true, bool DMassCut = true, bool LoosePIDCuts = true, BMassCuts = true);
    /**
     * Truth matching cuts
     */
    TCut GetTruthMatchingCuts() const;
    /**
     * Get all activated cuts as a TCut object
     */
    virtual TCut GetCuts() const;
  private:
    /**
     * "Pi" for \f$B\to D\pi$ and "K" for \f$B\to DK\f$
     */
    std::string m_DecayMode;
};
