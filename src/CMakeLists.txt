add_library(KKpipi ApplyCuts.cpp BaseCuts.cpp HighBMassCut.cpp TruthMatchingCuts.cpp)

target_include_directories(B2DhD2KKPiPiSelection PUBLIC ../include)

target_link_libraries(B2DhD2KKPiPiSelection PUBLIC ROOT::Physics ROOT::Minuit2 ROOT::Gpad)
