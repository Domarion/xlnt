cmake_minimum_required(VERSION 3.1)
project(xlnt_all)

#add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# CTest setup
# include (CTest) # Add this for valgrind support; CTest works without it
enable_testing()

# This indicates to CMakeLists in subdirectories that they are part of a larger project
set(COMBINED_PROJECT TRUE)

# Library type
option(STATIC "Set to ON to build xlnt as a static library instead of a shared library" ON)

# c++ language standard to use
set(XLNT_VALID_LANGS 17 20)
set(XLNT_CXX_LANG "17" CACHE STRING "c++ language features to compile with")
# enumerate allowed values for cmake gui
set_property(CACHE XLNT_CXX_LANG PROPERTY STRINGS ${XLNT_VALID_LANGS})
# validate value is in XLNT_VALID_LANGS
list(FIND XLNT_VALID_LANGS ${XLNT_CXX_LANG} index)
if(index EQUAL -1)
    message(FATAL_ERROR "XLNT_CXX_LANG must be one of ${XLNT_VALID_LANGS}")
endif()


# Optional components
option(TESTS "Set to ON to build test executable (in ./tests)" OFF)
option(SAMPLES "Set to ON to build executable code samples (in ./samples)" OFF)
option(BENCHMARKS "Set to ON to build performance benchmarks (in ./benchmarks)" OFF)
option(PYTHON "Set to ON to build Arrow conversion functions (in ./python)" OFF)

# Platform specific options
option(COVERAGE "Generate coverage data using gcov" OFF)

add_subdirectory(source)
