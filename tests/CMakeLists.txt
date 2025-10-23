include(ECMAddTests)
include_directories(AFTER "${CMAKE_CURRENT_SOURCE_DIR}/../src")

ecm_add_test(
    FontScanner.cpp
    TEST_NAME FontScanner
    LINK_LIBRARIES Qt6::Test libqfv
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
