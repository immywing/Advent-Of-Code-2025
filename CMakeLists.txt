cmake_minimum_required(VERSION 3.25)
set(PROJECT_NAME Advent-Of-Code-2025)
project(${PROJECT_NAME} VERSION 1.0)
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# FALLBACK FIX - Intellisense not working without: suppress Clang's "unused argument" error
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/std:c++latest>)
add_compile_options($<$<CXX_COMPILER_ID:Clang>:-Wno-unused-command-line-argument>)

# Fetch Google Test dependency:
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Force Google Test targets to compile with C++23 for compatibility
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
    src/utils/EmbeddedFile.h src/utils/EmbeddedFile.cpp
    src/utils/Memoization.h src/utils/Memoization.cpp
    src/solutions/day_1/Day1.h src/solutions/day_1/Day1.cpp
    src/solutions/day_2/Day2.h src/solutions/day_2/Day2.cpp
    src/solutions/day_3/Day3.h src/solutions/day_3/Day3.cpp
    src/solutions/day_4/Day4.h src/solutions/day_4/Day4.cpp
    src/solutions/day_5/Day5.h src/solutions/day_5/Day5.cpp
    src/solutions/day_6/Day6.h src/solutions/day_6/Day6.cpp
    src/solutions/day_7/Day7.h src/solutions/day_7/Day7.cpp
    src/solutions/day_8/Day8.h src/solutions/day_8/Day8.cpp
    src/solutions/day_9/Day9.h src/solutions/day_9/Day9.cpp
    src/solutions/day_11/Day11.h src/solutions/day_11/Day11.cpp
)

set(TEST_SOURCES
    #add as needed
    tests/EmbeddedFile/EmbeddedFile_Tests.cpp
    tests/day_9/Day9_Tests.cpp
)

# ==========================================================
# 1. AOC EXECUTABLE DEFINITION
# ==========================================================
add_executable(
    ${PROJECT_NAME}
    src/Advent-Of-Code-2025.cpp
    ${PROJECT_SOURCES}
)

# IntelliSense Fix for Clang/VS
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_GLOBAL_VCC_KIND ClangC23)

# Apply C++23 Feature
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Include Directories (Corrected variable usage and added src)
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${INPUTS_DIR}
)

# ==========================================================
# 2. TESTS EXECUTABLE DEFINITION
# ==========================================================
enable_testing()
add_executable(
    tests
    tests/tests.cpp
    ${TEST_SOURCES}
    ${PROJECT_SOURCES}
 )

# IntelliSense Fix for Clang/VS
set_property(TARGET tests PROPERTY VS_GLOBAL_VCC_KIND ClangC23)

# Apply C++23 Feature
target_compile_features(tests PRIVATE cxx_std_23)

# Include the src directory for Tests
target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/src/)

# Allow tests to access inputs
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