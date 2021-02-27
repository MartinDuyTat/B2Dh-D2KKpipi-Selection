add_executable(PrepareSample PrepareSample.cpp)
add_executable(TrainBDT TrainBDT.cpp)

target_link_libraries(PrepareSample PUBLIC B2DhD2KKPiPiSelection)
target_link_libraries(PrepareSample PUBLIC ROOT::Physics ROOT::RIO ROOT::Tree)

target_link_libraries(TrainBDT PUBLIC B2DhD2KKPiPiSelection)
target_link_libraries(TrainBDT PUBLIC ROOT::Physics ROOT::RIO ROOT::Tree ROOT::TMVA)

install(TARGETS PrepareSample TrainBDT DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../bin)
