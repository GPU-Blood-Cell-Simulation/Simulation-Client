#
# Tests
#
if (BUILD_TESTING)
    include(GoogleTest)

    # Sample tests
    add_executable(sample_tests 
        sample_test.cpp
    )
    target_link_libraries(sample_tests PRIVATE GTest::gtest_main)
    gtest_discover_tests(sample_tests)

    # utilities
    add_executable(json_config_tests
        json_config_tests.cpp
    )
    target_link_libraries(json_config_tests PRIVATE
        GTest::gtest_main
        test_client
    )
    gtest_discover_tests(json_config_tests)

endif()
