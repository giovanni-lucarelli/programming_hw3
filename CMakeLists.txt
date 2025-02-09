cmake_minimum_required(VERSION 3.16)

# Project name and language
project(PyPlusSci LANGUAGES CXX VERSION 1.0.0)

# Set C++ standard (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Global compiler flags
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Solve CMP0148 policy problem
if (POLICY CMP0148)
    cmake_policy(SET CMP0148 NEW)
endif()

# Add options to build specific modules
option(BUILD_DATAFRAME_BINDINGS "Build dataframe_bindings module" ON)
option(BUILD_INTERPOLATION_BINDINGS "Build interpolation_bindings module" ON)


# Set CMAKE_PREFIX_PATH for finding pybind11
# set(CMAKE_PREFIX_PATH "/home/elena/miniconda3/lib/python3.10/site-packages/pybind11/share/cmake/pybind11")

# Allow user to specify a custom pybind11 path
set(PYBIND11_CUSTOM_PATH "" CACHE PATH "Custom path to pybind11")

# Set the CMAKE_PREFIX_PATH for finding pybind11
if (PYBIND11_CUSTOM_PATH)
    list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_CUSTOM_PATH}")
endif()


# Find required packages
find_package(pybind11 REQUIRED)
find_package(GSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS json system filesystem)

# Verify Boost
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found")
endif()
message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")

# Include directories
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIRS}
    include
)

# Build dataframe_bindings module if the option is enabled
if (BUILD_DATAFRAME_BINDINGS)
    # Python bindings for DataFrame (includes DataFrame.cpp directly)
    pybind11_add_module(dataframe_bindings
        bindings/DataFrameBindings.cpp
        src/DataFrame.cpp
    )

    # Link Boost and GSL to DataFrame module
    target_link_libraries(dataframe_bindings PRIVATE
        Boost::boost
        Boost::json
        Boost::filesystem
        Boost::system
        GSL::gsl
    )
endif()

# Build interpolation_bindings module if the option is enabled
if (BUILD_INTERPOLATION_BINDINGS)
    # Python bindings for Interpolation (includes all interpolation sources directly)
    pybind11_add_module(interpolation_bindings
        bindings/InterpolationBindings.cpp
        src/Interpolator.cpp
        src/LinearInterpolator.cpp
        src/NewtonInterpolator.cpp
        src/GslPolynomialInterpolator.cpp
        src/CardinalCubicSpline.cpp
    )

    # Link Boost and GSL to Interpolation module
    target_link_libraries(interpolation_bindings PRIVATE
        Boost::boost
        Boost::system
        GSL::gsl
    )
endif()

message(STATUS "Configuration complete. Ready to build!")


# Add testing support
enable_testing()
option(BUILD_TESTS "Build test suite" OFF)

if (BUILD_TESTS)
    # Find GTest
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    # Create a library for shared sources
    add_library(dataframe_lib STATIC
        src/DataFrame.cpp
    )
    target_link_libraries(dataframe_lib PRIVATE Boost::boost Boost::json Boost::filesystem Boost::system GSL::gsl)

    add_library(interpolation_lib STATIC
        src/Interpolator.cpp
        src/LinearInterpolator.cpp
        src/NewtonInterpolator.cpp
        src/GslPolynomialInterpolator.cpp
        src/CardinalCubicSpline.cpp
    )
    target_link_libraries(interpolation_lib PRIVATE Boost::boost Boost::system GSL::gsl)

    # Test executables
    add_executable(test_dataframe tests/test_dataframe.cpp)
    target_link_libraries(test_dataframe PRIVATE dataframe_lib GTest::GTest GTest::Main pthread)

    add_executable(test_interpolation tests/test_interpolation.cpp)
    target_link_libraries(test_interpolation PRIVATE interpolation_lib GTest::GTest GTest::Main pthread)

    # Add tests to CTest
    add_test(NAME test_dataframe COMMAND test_dataframe)
    add_test(NAME test_interpolation COMMAND test_interpolation)
endif()
