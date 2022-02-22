// Martin Duy Tat 12th November 2020
/**
 * AmplitudePhaseSpace is a class that contains the information about how phase space is divided into bins
 * Add a new binning scheme by adding a derived class with the binning implemented
 * Bin numbers go from \f$i = 1, 2, 3, ...\f$, and \f$i = -1, -2, -3, ...\f$ for CP conjugated bins
 * Which events that are CP conjugates are defined by the binning scheme
 */

#ifndef AMPLITUDEPHASESPACE
#define AMPLITUDEPHASESPACE

#include<utility>
#include<vector>
#include"Amplitude.h"

class AmplitudePhaseSpace {
  public:
    /**
     * Constructor that creates a binning scheme with bins number of bins
     * @param bins Number of bins in the binning scheme
     */
    AmplitudePhaseSpace(const int &bins);
    /**
     * Function that determines which bin an event belongs to
     * Negative bin numbers are CP conjugates of the corresponding positive bin
     * If bin number is zero, the event has been vetoed, please skip this event
     * @param EventVector Vector with the four-momenta of KKpipi daughters, in the order K+ K- pi+ pi-
     * @return Bin number
     */
    int WhichBin(const std::vector<double> &EventVector) const;
    /**
     * Function that returns the number of bins in the binning scheme
     * @return Number of bins
     */
    int NumberOfBins() const;
    /**
     * Function that sets the veto boundary
     * @param Lower Lower edge of veto window
     * @param Upper Upper edge of veto window
     */
    void SetKSVeto(double Lower, double Upper);
    /**
     * Function that returns true if event is inside the veto window
     */
    bool isKSVeto(const std::vector<double> &P) const;
    /**
     * Function for setting the flag m_UseVariableBinWidths
     * Before setting this flag to true, the map BinEdgeMap must be initialised with the correct number of bin edges, otherwise this flag stays false
     * @param VariableBinWidth Flag that is true when variable bin widths are used
     */
    void UseVariableBinWidths(bool VariableBinWidths);
    /**
     * Function for setting the bin edges when variable bin widths are used
     * For \f$N\f$ bins, \f$(N - 2)/2\f$ inputs are required
     * \f$\delta_D = 0, \pm\pi\f$ are fixed bin edges, and the other $\f$N - 2\f$ are placed symmetrically around $\f$\delta = 0\f$, therefore $\f$(N - 2)/2\f$ bin edges must be specified
     * Bin edges must be positive, in increasing order!
     */
    void SetBinEdges(const std::vector<double> &BinEdges);
    /**
     * Function that determines which bin an event belongs to
     * @param event The event we want to determine the bin of
     * @return Bin number
     */
  private:
    /**
     * Number of bins in this binning scheme
     */
    int m_bins;
    /**
     * Veto window size around the \f$K_S^0\f$ mass, in units of \f$\text{GeV}\f$
     * If this is negative or zero, no veto is applied
     */
    std::pair<double, double> m_KSVeto;
    /**
     * Amplitude object to calculate the strong phase difference of an event
     */
    Amplitude m_amplitude;
    /**
     * When true, the bin edges will have variable bin widths along strong phase difference instead of uniformly spaced
     */
    bool m_UseVariableBinWidths = false;
    /**
     * Map that connects the upper bin edges with the bin numbers
     */
    std::map<double, int> m_BinMap;
};

#endif
