// Martin Duy Tat 25th Februrary 2021
/**
 * HighBMassCut is a class derived from BaseCuts, but overrides the \f$B\f$ mass cut and picks the higher mass band
 * Mainly used for selection candidates in the background training sample
 */

#ifndef HIGHMASSCUT
#define HIGHMASSCUT

#include"BaseCuts.h"

class HighBMassCut: public BaseCuts {
  public:
    /**
     * Constructor that sets all same options for cuts as BaseCuts, with the exception of BMassCuts, which is set as false as this is overridden in this class
     */
    HighBMassCuts(bool BachelorCuts = true, bool KaonDaughterCuts = true, bool DecayTreeFitCuts = true, bool DMassCut = true, bool LoosePIDCuts = true);
    /** 
     * Cut on \f$B\f$ mass after running DecayTreeFitter, selecting background from the high mass band
     */
    virtual TCut BMassCut() const;
    /**
     * Apply all activated cuts
     */
    viritual TCut ApplyCuts() const;
};
