// Martin Duy Tat 12th November 2020

#include<utility>
#include<vector>
#include<map>
#include<complex>
#include"AmplitudePhaseSpace.h"
#include"Amplitude.h"
#include"TMath.h"

AmplitudePhaseSpace::AmplitudePhaseSpace(const int &bins): m_bins(bins),
							   m_KSVeto(std::pair<double, double>({-1.0, -1.0})) {
}

int AmplitudePhaseSpace::NumberOfBins() const {
  return m_bins;
}

void AmplitudePhaseSpace::SetKSVeto(double Lower, double Upper) {
  m_KSVeto = std::pair<double, double>({Lower, Upper});
}

bool AmplitudePhaseSpace::isKSVeto(const std::vector<double> &P) const {
  if(m_KSVeto.first <= 0.0 || m_KSVeto.second <= 0.0) {
    return false;
  } else {
    double Mpipi = TMath::Sqrt(TMath::Power(P[11] + P[15], 2) -
                               TMath::Power(P[8]  + P[12], 2) - 
			       TMath::Power(P[9]  + P[13], 2) - 
			       TMath::Power(P[10] + P[14], 2));
    return Mpipi > m_KSVeto.first && Mpipi < m_KSVeto.second;
  }
}

void AmplitudePhaseSpace::UseVariableBinWidths(bool VariableBinWidths) {
  if(VariableBinWidths && static_cast<int>(m_BinMap.size()) == NumberOfBins()) {
    m_UseVariableBinWidths = true;
  } else {
    m_UseVariableBinWidths = false;
  }
}

void AmplitudePhaseSpace::SetBinEdges(const std::vector<double> &BinEdges) {
  m_BinMap.clear();
  int BinNumberCounter = 1;
  for(auto it = BinEdges.rbegin(); it != BinEdges.rend(); it++) {
    m_BinMap.insert({-*it, BinNumberCounter});
    ++BinNumberCounter;
  }
  m_BinMap.insert({0.0, BinNumberCounter});
  ++BinNumberCounter;
  for(const auto &edge : BinEdges) {
    m_BinMap.insert({edge, BinNumberCounter});
    ++BinNumberCounter;
  }
  m_BinMap.insert({TMath::Pi(), BinNumberCounter});
}

int AmplitudePhaseSpace::WhichBin(const std::vector<double> &EventVector) const {
  if(isKSVeto(EventVector)) {
    return 0;
  }
  std::complex<double> D_amplitude, Dbar_amplitude;
  double phase, rD;
  D_amplitude = m_amplitude(EventVector, +1);
  Dbar_amplitude = m_amplitude(EventVector, -1);
  if(TMath::IsNaN(D_amplitude.real()) || TMath::IsNaN(D_amplitude.imag()) || TMath::IsNaN(Dbar_amplitude.real()) || TMath::IsNaN(Dbar_amplitude.imag())) {
    return 0;
  }
  phase = std::arg(D_amplitude*std::conj(Dbar_amplitude));
  rD = std::norm(D_amplitude/Dbar_amplitude);
  int BinNumber;
  if(m_UseVariableBinWidths) {
    BinNumber = m_BinMap.lower_bound(phase)->second;
  } else {
    BinNumber = static_cast<int>((phase + TMath::Pi())/(2*TMath::Pi()/NumberOfBins())) + 1;
  }
  if(rD < 1) {
    return BinNumber;
  } else {
    return -(NumberOfBins() + 1 - BinNumber);
  }
}
