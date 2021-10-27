set(CMAKE_INSTALL_RPATH ${KKPIPI_BINNED_FIT_PATH}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable(ApplyFinalCuts ApplyFinalCuts.cpp)
add_executable(BinEvents BinEvents.cpp)
add_executable(CheckEventNumbers CheckEventNumbers.cpp)
add_executable(BDTClassifier BDTClassifier.cpp)
add_executable(PrepareSample PrepareSample.cpp)
add_executable(RemoveMultipleCandidates RemoveMultipleCandidates.cpp)
add_executable(TrainBDT TrainBDT.cpp)

target_link_libraries(ApplyFinalCuts PUBLIC B2DhD2KKPiPiSelection)
target_link_libraries(ApplyFinalCuts PUBLIC ROOT::Physics ROOT::RIO ROOT::Tree)

target_link_libraries(BDTClassifier PUBLIC B2DhD2KKPiPiSelection)
target_link_libraries(BDTClassifier PUBLIC ROOT::Physics ROOT::RIO ROOT::Tree)

target_include_directories(BinEvents PUBLIC ${KKPIPI_BINNED_FIT_PATH}/include)
target_link_libraries(BinEvents PUBLIC B2DhD2KKPiPiSelection)
target_link_libraries(BinEvents PUBLIC ROOT::Physics ROOT::RIO ROOT::Tree)
target_link_libraries(BinEvents PUBLIC ${KKPIPI_BINNED_FIT_LIB} -ldl)

target_link_libraries(CheckEventNumbers PUBLIC B2DhD2KKPiPiSelection)
target_link_libraries(CheckEventNumbers PUBLIC ROOT::Physics ROOT::RIO ROOT::Tree)

target_link_libraries(PrepareSample PUBLIC B2DhD2KKPiPiSelection)
target_link_libraries(PrepareSample PUBLIC ROOT::Physics ROOT::RIO ROOT::Tree)

target_link_libraries(RemoveMultipleCandidates PUBLIC B2DhD2KKPiPiSelection)
target_link_libraries(RemoveMultipleCandidates PUBLIC ROOT::Physics ROOT::RIO ROOT::Tree ROOT::TMVA)

target_link_libraries(TrainBDT PUBLIC B2DhD2KKPiPiSelection)
target_link_libraries(TrainBDT PUBLIC ROOT::Physics ROOT::RIO ROOT::Tree ROOT::TMVA)

install(TARGETS ApplyFinalCuts BDTClassifier BinEvents CheckEventNumbers PrepareSample RemoveMultipleCandidates TrainBDT DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../bin)
