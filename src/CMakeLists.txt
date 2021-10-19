add_library(B2DhD2KKPiPiSelection ApplyCuts.cpp BaseCuts.cpp BDTVariables.cpp CharmlessCuts.cpp CombinatorialBMassCut.cpp EventNumbers.cpp FinalCuts.cpp HighBMassCut.cpp TruthMatchingCuts.cpp Utilities.cpp)

target_include_directories(B2DhD2KKPiPiSelection PUBLIC ../include)

target_link_libraries(B2DhD2KKPiPiSelection PUBLIC ROOT::Physics ROOT::TMVA)
