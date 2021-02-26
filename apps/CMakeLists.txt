add_executable(PrepareSignalTrainingSample PrepareSignalTrainingSample.cpp)

target_link_libraries(PrepareSignalTrainingSample PUBLIC B2DhD2KKPiPiSelection)
target_link_libraries(PrepareSignalTrainingSample PUBLIC ROOT::Physics ROOT::RIO ROOT::Tree)

install(TARGETS PrepareSignalTrainingSample DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../bin)
