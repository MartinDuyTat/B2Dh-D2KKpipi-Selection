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
     * @param Year Year of dataset
     * @param BachelorCuts Set to true to apply cuts on bachelor particle
     * @param KaonDaughterCuts Set to true to apply cuts on Kaon daugthers
     * @param DecayTreeFitCuts Set to true to apply cuts on DecayTreeFitter convergence
     * @param DMassCut Set to true to apply cuts on \f$D\f$ mass
     * @param LoosePIDCuts Set to true to apply loose PID cuts (already present in Run 2 stripping, but not Run 1)
     * @param TriggerCuts Set to true to apply trigger requirements
     * @param BMassCut Set to true to apply cuts on \f$B\f$ mass
     */
    BaseCuts(int Year, bool BachelorCuts = true, bool KaonDaughterCuts = true, bool DecayTreeFitCuts = true, bool DMassCut = true, bool LoosePIDCuts = true, bool TriggerCuts = true, bool BMassCut = true);
    /**
     * Trivial destructor
     */
    virtual ~BaseCuts();
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
    virtual TCut DMassCut() const;
    /**
     * Loose PID cuts
     */
    TCut LoosePIDCuts() const;
    /**
     * Trigger cuts
     */
    TCut TriggerCuts() const;
    /** 
     * Cut on \f$B\f$ mass after running DecayTreeFitter
     */
    virtual TCut BMassCut() const;
    /**
     * Get all activated cuts as a TCut object
     */
    virtual TCut GetCuts() const;
  private:
    /**
     * Year dataset was taken
     */
    int m_Year;
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
    bool m_DecayTreeFitCut;
    /**
     * Flag for \f$D\f$ mass cut
     */
    bool m_DMassCut;
    /**
     * Flag for loose PID cuts
     */
    bool m_LoosePIDCuts;
    /**
     * Flag for trigger cuts
     */
    bool m_TriggerCuts;
    /**
     * Flag for \f$D\f$ mass cut
     */
    bool m_BMassCut;
};

#endif
