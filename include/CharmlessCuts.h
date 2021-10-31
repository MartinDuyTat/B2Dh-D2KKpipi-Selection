// Martin Duy Tat 19th March 2021
/**
 * CharmlessCuts is a class derived from BaseCuts, but overrides the \f$D\f$ mass cut and picks the lower mass sideband and removes the DecayTreeFitter convergence requirement
 * Mainly used for selection candidates in the sample for studying charmless background
 */

#ifndef CHARMLESSCUTS
#define CHARMLESSCUTS

#include<string>
#include"BaseCuts.h"
#include"TCut.h"

class CharmlessCuts: public BaseCuts {
  public:
    /**
     * Constructor that sets all same options for cuts as BaseCuts, with the exception of DMassCut, which is set as false as this is overridden in this class, and DecayTreeFit has been turned off
     */
    CharmlessCuts(const std::string &DDecayMode, int Year, bool BachelorCuts = true, bool KaonDaughterCuts = false, bool LoosePIDCuts = true, bool TriggerCuts = true, bool BMassCut = true);
    /**
     * Tritial destructor
     */
    virtual ~CharmlessCuts();
    /** 
     * Cut on \f$D\f$ mass, selecting charmless background from the low mass sideband
     */
    virtual TCut DMassCut() const;
    /** 
     * Cut on \f$B\f$ mass, selecting the same range as before but using the reconstructed $B$ mass instead of the one from DecayTreeFitter
     */
    virtual TCut BMassCut() const;
    /**
     * Get all activated cuts as a TCut object
     */
    virtual TCut GetCuts() const;
};

#endif
