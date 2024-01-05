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

    # json config
    add_executable(json_config_tests
        json_config_tests.cpp
    )
    target_link_libraries(json_config_tests PRIVATE
        GTest::gtest_main
        test_client
    )
    gtest_discover_tests(json_config_tests)

    # vein generation
    add_executable(vein_generator_tests
        vein_generator_tests.cpp
    )
    target_link_libraries(vein_generator_tests PRIVATE
        GTest::gtest_main
        test_client
    )
    gtest_discover_tests(vein_generator_tests)

endif()
