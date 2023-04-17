cmake_minimum_required(VERSION 3.15)
project(expression_template_safety_tests)

enable_testing()

add_library(shared-config INTERFACE)
add_library(ets::base-config ALIAS shared-config)

target_compile_features(shared-config INTERFACE cxx_std_17)

find_package(Eigen3 REQUIRED)

add_executable(test_1_1 src/main.cpp)
target_compile_definitions(test_1_1 PRIVATE TEST_1_1)
target_link_libraries(test_1_1 ets::base-config Eigen3::Eigen)
add_test(NAME Test_1_1 COMMAND ${CMAKE_COMMAND} --build . --target test_1_1 --config $<CONFIGURATION>)

add_executable(test_5_1 src/main.cpp)
target_compile_definitions(test_5_1 PRIVATE TEST_5_1)
target_link_libraries(test_5_1 ets::base-config Eigen3::Eigen)
set_target_properties(test_5_1 PROPERTIES
    EXCLUDE_FROM_ALL TRUE
    EXCLUDE_FROM_DEFAULT_BUILD TRUE
)
add_test(NAME Test_5_1 COMMAND ${CMAKE_COMMAND} --build . --target test_5_1 --config $<CONFIGURATION>)
set_tests_properties(Test_5_1 PROPERTIES PASS_REGULAR_EXPRESSION "The LHS references an r-value past its lifetime.")
