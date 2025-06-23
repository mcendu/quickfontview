include(ECMAddTests)
include_directories(AFTER "${CMAKE_CURRENT_SOURCE_DIR}/../src")

ecm_add_test(
    FontScanner.cpp
    ../src/FontScanner.cpp
    ../src/FontFeatures.cpp
    TEST_NAME FontScanner
    LINK_LIBRARIES Qt6::Test Qt6::Quick ${HARFBUZZ_LIBRARIES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
