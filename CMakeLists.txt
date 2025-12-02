cmake_minimum_required(VERSION 3.25) # Updated to a modern version for C++23 support
set(PROJECT_NAME Advent-Of-Code-2025)
project(${PROJECT_NAME} VERSION 1.0)
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

# Enforce C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/std:c++23>)

# Fetch Google Test dependency:
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

if (TARGET gtest)
    target_compile_features(gtest PUBLIC cxx_std_23)
endif()
if (TARGET gtest_main)
    target_compile_features(gtest_main PUBLIC cxx_std_23)
endif()

set(CREATE_INPUTS_SCRIPT ${CMAKE_BINARY_DIR}/create_inputs_script.cmake)
set(INPUTS_DIR ${CMAKE_SOURCE_DIR}/inputs)

set(SCRIPT_CONTENT "
# This script is executed during the build step using 'cmake -P'.
file(MAKE_DIRECTORY \"${INPUTS_DIR}\")

foreach(i RANGE 1 12)
    set(INPUT_FILE \"${INPUTS_DIR}/day_\${i}.txt\")
    if (NOT EXISTS \${INPUT_FILE})
        message(STATUS \"[Build Step] Creating empty input file: \${INPUT_FILE}\")
        # Writing an empty string to create an empty file
        file(WRITE \${INPUT_FILE} \"\")
    endif()
endforeach()
")

file(WRITE ${CREATE_INPUTS_SCRIPT} "${SCRIPT_CONTENT}")

add_custom_target(create_inputs
    COMMAND ${CMAKE_COMMAND} -P ${CREATE_INPUTS_SCRIPT}
    COMMENT "Ensuring input files exist before compilation."
)

set(PROJECT_SOURCES
    #add as needed
    src/utils/EmbeddedFile.h
    src/utils/EmbeddedFile.cpp
    src/solutions/day_1/Day1.h src/solutions/day_1/Day1.cpp
    src/solutions/day_2/Day2.h src/solutions/day_2/Day2.cpp
)

set(TEST_SOURCES
    #add as needed
    tests/EmbeddedFile/EmbeddedFile_Tests.cpp
)

# AOC executable
add_executable(
    ${PROJECT_NAME}
    src/Advent-Of-Code-2025.cpp
    ${PROJECT_SOURCES}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Allow the main executable to include files from the 'inputs' directory
target_include_directories(${PROJECT_NAME} PRIVATE INPUTS_DIR)

# Tests
enable_testing()
add_executable(
    tests
    tests/tests.cpp
    ${TEST_SOURCES}
    ${PROJECT_SOURCES}
 )

target_compile_features(tests PRIVATE cxx_std_23)

# Include the src directory for Tests (so tests can find project headers)
target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/src/)
# Allow tests to access inputs (if needed by tests)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/inputs)

target_link_libraries(
    tests
    PRIVATE gtest
    PRIVATE gtest_main
)

# Add tests to CTest
add_test(NAME tests COMMAND tests)
add_dependencies(${PROJECT_NAME} create_inputs)
add_dependencies(tests create_inputs)