cmake_minimum_required(VERSION 3.10)

project(Template)

add_subdirectory(testing)

add_library(settings INTERFACE)
target_compile_features(settings INTERFACE cxx_std_17)
target_compile_options(settings INTERFACE -pedantic -Wall -Werror)

# Test
add_executable(test source/test-result.cc)
target_link_libraries(test PRIVATE testing settings)
add_custom_target(run-tests ALL test)
