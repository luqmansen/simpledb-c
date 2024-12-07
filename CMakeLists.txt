cmake_minimum_required(VERSION 3.29)
set(CMAKE_C_STANDARD 17)

project(simpledb)
# after `project` is called, the following vars are available
# PROJECT_SOURCE_DIR
# PROJECT_BINARY_DIR


# Project-wide include directory configuration.
include_directories(${PROJECT_SOURCE_DIR}/include)


# Source files
file (GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

# MAIN -- separate executable
# Key idea: SEPARATE OUT your main() function into its own file so it can be its
# own executable. Separating out main() means you can add this library to be
# used elsewhere (e.g linking to the test executable).
list(REMOVE_ITEM SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.c)


# Compile source files into a library
add_library(simpledb_lib ${SOURCE_FILES})


# main is separate (e.g. library client)
add_executable(simpledb ${PROJECT_SOURCE_DIR}/src/main.c)


# link main against the library
target_link_libraries(simpledb simpledb_lib)



### testing ###
add_subdirectory(${PROJECT_SOURCE_DIR}/tests/googletest)
enable_testing()

# include gtest library. gtest_SOURCE_DIR is available due to 'project(gtest) above
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

## test files
file(GLOB TEST_SOURCE_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

add_executable(runUnitTests ${TEST_SOURCE_FILES}
        tests/test_add.cpp)

# Linking gtest-related
target_link_libraries(runUnitTests gtest gtest_main)


# link the test with lib
target_link_libraries(runUnitTests simpledb_lib)


# this to allow `make test` command and see all the test run,
# instead manually running executable runUnitTest
add_test(UnitTests runUnitTests)