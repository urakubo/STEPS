cmake_minimum_required(VERSION 3.0.0)
if(POLICY CMP0042)
    # Use rpath on Mac OS X
    cmake_policy(SET CMP0042 NEW)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

project(STEPS)

set(VERSION_MAJOR 3)
set(VERSION_MINOR 4)
set(VERSION_PATCH 1)
set(STEPS_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# OPTIONS
option(TARGET_NATIVE_ARCH "Generate non-portable arch-specific code" ON)
option(USE_BDSYSTEM_LAPACK "Use new BDSystem/Lapack code for E-Field solver" OFF)
set(USE_MPI   "Default" CACHE STRING "Use MPI for parallel solvers")
set(USE_PETSC "Default" CACHE STRING "Use PETSC library for parallel E-Field solver")
if (NOT USE_MPI MATCHES "^(Default|True|False)$")
    message(FATAL_ERROR "Acceptable values for USE_MPI are: \"Default\", \"True\", \"False\"!")
endif()
if (NOT USE_PETSC MATCHES "^(Default|True|False)$")
    message(FATAL_ERROR "Acceptable values for USE_PETSC are: \"Default\", \"True\", \"False\"!")
endif()

# Valgrind
set(VALGRIND "" CACHE STRING "Valgrind plus arguments for testing")
if(NOT VALGRIND STREQUAL "")
    file(GLOB valgrind_supps ${CMAKE_CURRENT_SOURCE_DIR}/test/ci/valgrind/*.supp)
    foreach(valgrind_supp IN LISTS valgrind_supps)
        LIST(APPEND valgrind_supps_cmd --suppressions=${valgrind_supp})
    endforeach()
    set(VALGRIND "${VALGRIND}" ${valgrind_supps_cmd})
endif()

# Compiler options
# -------------------------------------------------------------------
include(CMake/Compiler.cmake)

include(CMake/steps_portability_check.cmake)

option(USE_CLANG_TIDY "Perform C++ static analysis while compiling" FALSE)
if(USE_CLANG_TIDY)
    find_package(CLANG_TIDY REQUIRED)
    if(CLANG_TIDY_FOUND)
        cmake_minimum_required(VERSION 3.6)
        set(CLANG_TIDY_ARGS "" CACHE STRING "clang-tidy command options")
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE}" ${CLANG_TIDY_ARGS})
    else()
        message(ERROR "Could not find clang-tidy utility")
    endif()
endif()

# Nuke any -DNDEBUG in the compiler options introduced by CMake.
include(CMake/ManipulateVariables.cmake)
foreach(var_name ${flag_vars})
    remove_word(${var_name} "-DNDEBUG")
endforeach()

# for debug symbol
include(CMake/UseDebugSymbols.cmake)

set(CMAKE_CXX_FLAGS "${CXX_DIALECT_OPT_CXX11} ${CMAKE_CXX_FLAGS}")

if(TARGET_NATIVE_ARCH)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_OPT_ARCH_NATIVE}")
endif()

# Code coverage
SET(CODECOV_GCOVR_OPTIONS "-v --filter='.*/src/steps/.*'")
include(UseCodeCoverage)
if(ENABLE_CODECOVERAGE)
    install(
        DIRECTORY ${CMAKE_BINARY_DIR}/${CODECOV_HTMLOUTPUTDIR}/
        DESTINATION share/steps/${STEPS_VERSION}/coverage
    )
    install(
        FILES ${CMAKE_BINARY_DIR}/${CODECOV_XMLOUTPUTFILE}
        DESTINATION share/steps/${STEPS_VERSION}/coverage
    )
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()


# Requirements
# -------------------------------------------------------------------
find_package(PythonInterpLibs)
find_package(Threads REQUIRED)


# if USE_MPI is
#   - False:   we do not search it
#   - True:    we search and require it
#   - Default: we search it, and we use it only if found
if (USE_MPI MATCHES "^(Default|True)$")
    if (USE_MPI STREQUAL "True")
        find_package(MPI REQUIRED)
    elseif (USE_MPI STREQUAL "Default")
        find_package(MPI)
    endif()
    if (MPI_FOUND)
        add_definitions(-DUSE_MPI)
        find_program(MPIRUN
            NAMES mpirun
            HINTS ${MPI_HOME} $ENV{MPI_HOME}
            PATHS ${_MPI_PREFIX_PATH}
            PATH_SUFFIXES bin
            DOC "Executable for running MPI programs.")
    endif()
endif()

# see USE_MPI options above
if (USE_PETSC MATCHES "^(Default|True)$")
    if (USE_PETSC STREQUAL "True")
        if (NOT MPI_FOUND)
            message(FATAL_ERROR "PETSC reqires MPI!")
        endif()
        find_package(PETSC REQUIRED)
    elseif (USE_PETSC STREQUAL "Default")
        if (NOT MPI_FOUND)
            message(WARNING "Building without PETSC. If desired enable finding MPI libs as well!")
        else()
            find_package(PETSC)
        endif()
    endif()
    if (PETSC_FOUND)
        add_definitions(-DUSE_PETSC)
    endif()
endif()


#OpenBlas only made it to CMake in 3.6. Until then we include version from 3.6
find_package(BLAS REQUIRED)

## ignore LAPACK if OpenBlas is found
if(NOT BLA_VENDOR STREQUAL "OpenBLAS")
    find_package(LAPACK)
else() # if OpenBlas is used, then we have Lapack
    set(LAPACK_FOUND true)
endif()

# OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_FLAGS "${CMAKE_FLAGS} ${OpenMP_FLAGS}")
endif()

# Linking Libs - required in src and pysteps
list(APPEND libsteps_link_libraries ${BLAS_LIBRARIES})
if(MPI_FOUND)
    list(APPEND libsteps_link_libraries ${MPI_CXX_LIBRARIES} ${MPI_C_LIBRARIES})
    set(MPI_FOUND_HEADERS ${MPI_C_INCLUDE_PATH})
endif()
if(LAPACK_FOUND)
    list(APPEND libsteps_link_libraries ${LAPACK_LIBRARIES})
endif()
if(PETSC_FOUND)
    list(APPEND libsteps_link_libraries ${PETSC_LIBRARIES})
endif()


if(USE_BDSYSTEM_LAPACK AND NOT LAPACK_FOUND)
    message(STATUS "Unable to find LAPACK; will not build BDSystem/Lapack code.")
endif()


#### Python Install Path ####
set(_default_prefixes "/usr/local" "/usr")
list(FIND _default_prefixes ${CMAKE_INSTALL_PREFIX} _index)
if(${_index} GREATER -1)
    # Default installations install Python to default site-packages
    set(_py_install_prefix ${PYTHON_SITE_PACKAGES})
else()
    set(_py_install_prefix ${CMAKE_INSTALL_PREFIX})
endif()

set(PYTHON_INSTALL_PREFIX ${_py_install_prefix} CACHE PATH "Path to install steps Python package")
message(STATUS "PYTHON packages being installed to ${PYTHON_INSTALL_PREFIX}. To change use -DPYTHON_INSTALL_PREFIX=<dir>")


# Python bindings tech
# Makes steps Python bindings based on Cython
find_package(Cython 0.25.1 REQUIRED)
add_subdirectory(pysteps)

# Makes libsteps-obj, libsteps.so
add_subdirectory(src)

# Make testing targets
enable_testing()
add_subdirectory(test)
