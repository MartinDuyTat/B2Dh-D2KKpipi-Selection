// Martin Duy Tat 25th February 2021
/**
 * HighBMassCut is a class derived from BaseCuts, but overrides the \f$B\f$ mass cut and picks the higher mass band
 * Mainly used for selection candidates in the background training sample
 */

#ifndef HIGHBMASSCUT
#define HIGHBMASSCUT

#include<string>
#include"BaseCuts.h"
#include"TCut.h"

class HighBMassCut: public BaseCuts {
  public:
    /**
     * Constructor that sets all same options for cuts as BaseCuts, with the exception of BMassCuts, which is set as false as this is overridden in this class
     */
    HighBMassCut(const std::string &DDecayMode, int Year, bool BachelorCuts = true, bool KaonDaughterCuts = true, bool DecayTreeFitCuts = true, bool DMassCut = true, bool LoosePIDCuts = true);
    /**
     * Tritial destructor
     */
    virtual ~HighBMassCut();
    /** 
     * Cut on \f$B\f$ mass after running DecayTreeFitter, selecting background from the high mass band
     */
    virtual TCut BMassCut() const;
    /**
     * Get all activated cuts as a TCut object
     */
    virtual TCut GetCuts() const;
};

#endif
