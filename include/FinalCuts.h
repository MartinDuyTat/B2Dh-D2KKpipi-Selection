// Martin Duy Tat 8th March 2021
/**
 * FinalCuts is a class which create the final cuts for B selection
 * The cuts are PID cuts, DecayTreeFitter \f$\chi^2\f$ cut, flight significance cut and BDT cut
 */

#ifndef FINALCUTS
#define FINALCUTS

#include<string>
#include"TCut.h"

class FinalCuts {
  public:
    /**
     * Default constructor with a few options, which are true by default
     * @param BMode "pi" for \f$B\to D\pi\f$ and "K" for \f$B\to DK\f$
     * @param DMode "KKpipi" or "pipipipi"
     * @param BDTcut BDT cut threshold (between \f$-1\f$ and \f$+1\f$)
     * @param BachelorPIDCut Set to true to apply PID cut on bachelor particle
     * @param KaonDaughterPIDCut Set to true to apply PID cut on kaon daughters
     * @param FlightSignificanceCut Set to true to apply cut on flight significance
     * @param DTFChi2Cut Set to true to apply cuts on DecayTreeFitter \f$\chi^2\f$ (not necessary because it's a BDT training variable)
     */
    FinalCuts(const std::string &BMode, const std::string &DMode, double BDTcut = 0.0, bool BachelorPIDCuts = true, bool KaonDaughterPIDCut = true, bool FlightSignificanceCut = true, bool DTFChi2Cut = false, bool KSVeto = true);
    /**
     * Trivial destructor
     */
    virtual ~FinalCuts();
    /**
     * Cut on BDT output
     */
    TCut BDTCut() const;
    /** 
     * Cut on bachelor PID
     */
    TCut BachelorPIDCut() const;
    /** 
     * Cut on \f$K^\pm\f$ daughter PID
     */
    TCut KaonDaughterPIDCut() const;
    /** 
     * Cut on flight significance
     */
    TCut FlightSignificanceCut() const;
    /** 
     * Cut DecayTreeFitter \f$\chi^2\f$
     */
    TCut DTFChi2Cut() const;
    /**
     * \f$K_S\f$ veto for the \f$\pi\pi\pi\pi\f$ mode
     * For \f$KK\pi\pi$ the \f$K_S\f$ veto is already a part of the binning scheme
     */
    TCut KSVetoCut() const;
    /**
     * Get all activated cuts as a TCut object
     */
    TCut GetCuts() const;
  private:
    /**
     * B decay mode
     */
    std::string m_BMode;
    /**
     * D decay mode
     */
    std::string m_DMode;
    /**
     * BDT cut threshold
     */
    double m_BDTcut;
    /**
     * Flag for bachelor PID particle cuts
     */
    bool m_BachelorPIDCut;
    /**
     * Flag for kaon daughter PID cuts
     */
    bool m_KaonDaughterPIDCut;
    /**
     * Flag for flight significance cut
     */
    bool m_FlightSignificanceCut;
    /**
     * Flag for DecayTreeFitter \f$\chi^2\f$ cut
     */
    bool m_DTFChi2Cut;
    /**
     * Flat for \f$K_S\f$ veto cut
     */
    bool m_KSVeto;
};

#endif
