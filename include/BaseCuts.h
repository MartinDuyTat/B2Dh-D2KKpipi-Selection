// Martin Duy Tat 25th Februrary 2021
/**
 * BaseCuts is a class with the most common cuts used in B selection
 * The user can either apply each cut one by one or call the ApplyBaseCuts member function, which applies all the ones activated
 */

#ifndef BASECUTS
#define BASECUTS

#include"TCut.h"

class BaseCuts {
  public:
    /**
     * Default constructor with a few options, which are true by default
     * @param
     */
    BaseCuts(bool BachelorCuts = true, bool KaonDaugtherCuts = true, DecayTreeFitCuts = true, DMassCut = true, LoosePIDCuts = true);
    /**
     * Base cuts on bachelor particle
     */
    TCut BachelorCuts();
    /**
     * Cuts on the Kaon daughter cuts
     */
    TCut KaonDaughterCuts();
    /**
     * Cut on DecayTreeFit convergence
     */
    TCut DecayTreeFitCut();
    /**
     * Cut on \f$D\f$ mass
     */
    TCut DMassCut();
    /**
     * Loose PID cuts
     */
    TCut LoosePIDCuts();
    /**
     * Apply all activated cuts
     */
    TCut ApplyBaseCuts();
  private:
    /**
     * Flag for bachelor particle cuts
     */
    bool m_BachelorCuts;
    /**
     * Flag for kaon daughter cuts
     */
    bool m_KaonDaughterCuts;
    /**
     * Flag for DecayTreeFit cuts
     */
    bool m_DecayTreeFitCuts;
    /**
     * Flag for \f$D\f$ mass cut
     */
    bool m_DMassCut;
    /**
     * Flag for loose PID cuts
     */
    bool m_LoosePIDCuts;
};
