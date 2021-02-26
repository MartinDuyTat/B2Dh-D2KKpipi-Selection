add_executable(PrepareSample PrepareSample.cpp)

target_link_libraries(PrepareSample PUBLIC B2DhD2KKPiPiSelection)
target_link_libraries(PrepareSample PUBLIC ROOT::Physics ROOT::RIO ROOT::Tree)

install(TARGETS PrepareSample DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../bin)
