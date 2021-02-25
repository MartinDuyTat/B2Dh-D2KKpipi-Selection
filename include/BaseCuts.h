// Martin Duy Tat 25th February 2021
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
    BaseCuts(bool BachelorCuts = true, bool KaonDaughterCuts = true, bool DecayTreeFitCuts = true, bool DMassCut = true, bool LoosePIDCuts = true, bool BMassCut = true);
    /**
     * Base cuts on bachelor particle
     */
    TCut BachelorCuts() const;
    /**
     * Cuts on the Kaon daughter cuts
     */
    TCut KaonDaughterCuts() const;
    /**
     * Cut on DecayTreeFit convergence
     */
    TCut DecayTreeFitCut() const;
    /**
     * Cut on \f$D\f$ mass
     */
    TCut DMassCut() const;
    /**
     * Loose PID cuts
     */
    TCut LoosePIDCuts() const;
    /** 
     * Cut on \f$B\f$ mass after running DecayTreeFitter
     */
    TCut BMassCut() const;
    /**
     * Apply all activated cuts
     */
    TCut ApplyBaseCuts() const;
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
    /**
     * Flag for \f$D\f$ mass cut
     */
    bool m_BMassCut;
};
