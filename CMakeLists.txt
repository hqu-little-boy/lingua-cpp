cmake_minimum_required(VERSION 3.15)
project(lingua_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    # Force compiler to use UTF-8 for IPA constants
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
elseif (NOT APPLE)
    # Linux flags
    string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -Wl,-rpath,'$ORIGIN'")
    string(APPEND CMAKE_C_FLAGS " -Wall -Wextra")
endif ()

# Collect source files
file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "src/*.h"
        "src/*.hpp"
)

# Create the library
add_library(lingua_cpp ${SOURCES})
target_include_directories(lingua_cpp PUBLIC include)

# Add third-party dependencies
add_subdirectory(3rd/brotli)
target_include_directories(lingua_cpp PUBLIC 3rd/brotli/c)

add_subdirectory(3rd/simdjson)
target_include_directories(lingua_cpp PUBLIC 3rd/simdjson/include)

add_subdirectory(3rd/spdlog)
target_include_directories(lingua_cpp PUBLIC 3rd/spdlog/include)

add_subdirectory(3rd/utfcpp)
target_include_directories(lingua_cpp PUBLIC 3rd/utfcpp/source)

target_link_libraries(lingua_cpp PUBLIC
        brotlidec
        simdjson::simdjson
        utf8cpp
        spdlog
)

# Create unit tests
enable_testing()
add_executable(unit_tests tests/unit_tests.cpp)
add_executable(comprehensive_tests tests/comprehensive_tests.cpp)

# Add Google Test
add_subdirectory(3rd/googletest)
target_include_directories(unit_tests PRIVATE
        3rd/googletest/googletest/include
        3rd/googletest/googlemock/include
        include
)

target_include_directories(comprehensive_tests PRIVATE
        3rd/googletest/googletest/include
        3rd/googletest/googlemock/include
        include
)

# Link libraries to unit tests
target_link_libraries(unit_tests PRIVATE
        lingua_cpp
        gtest
        gtest_main
        brotlidec
        simdjson::simdjson
        utf8cpp
        spdlog
)

target_link_libraries(comprehensive_tests PRIVATE
        lingua_cpp
        gtest
        gtest_main
        brotlidec
        simdjson::simdjson
        utf8cpp
        spdlog
)

add_test(NAME unit_tests COMMAND unit_tests)
add_test(NAME comprehensive_tests COMMAND comprehensive_tests)

# Create example executables
add_executable(builder_configurations examples/builder_configurations.cpp)
target_include_directories(builder_configurations PRIVATE include)
target_link_libraries(builder_configurations PRIVATE lingua_cpp)

add_executable(detection_example examples/detection_example.cpp)
target_include_directories(detection_example PRIVATE include)
target_link_libraries(detection_example PRIVATE lingua_cpp)

add_executable(confidence_values_example examples/confidence_values_example.cpp)
target_include_directories(confidence_values_example PRIVATE include)
target_link_libraries(confidence_values_example PRIVATE lingua_cpp)