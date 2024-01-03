#
# Tests
#

if (BUILD_TESTING)

    # Sample tests
    add_executable(sample_tests sample_test.cpp)
    target_link_libraries(sample_tests PRIVATE GTest::gtest_main)
    
    include(GoogleTest)
    gtest_discover_tests(sample_tests)
    
endif()