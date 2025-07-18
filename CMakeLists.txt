cmake_minimum_required(VERSION 3.15...3.27)

set(BALATRO_GYM_CORE_DIR "src/balatro_gym/_core")

project(balatro_gym
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX
)

# Use CXX20 Standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# Warn if the user invokes CMake directly
if (NOT SKBUILD)
  message(WARNING "\
  This CMake file is meant to be executed using 'scikit-build-core'.
  Running it directly will almost certainly not produce the desired
  result. If you are a user trying to install this package, use the
  command below, which will install all necessary build dependencies,
  compile the package in an isolated environment, and then install it.
  =====================================================================
   $ pip install .
  =====================================================================
  If you are a software developer, and this is your own package, then
  it is usually much more efficient to install the build dependencies
  in your environment once and use the following command that avoids
  a costly creation of a new virtual environment at every compilation:
  =====================================================================
   $ pip install nanobind scikit-build-core[pyproject]
   $ pip install --no-build-isolation -ve .
  =====================================================================
  You may optionally add -Ceditable.rebuild=true to auto-rebuild when
  the package is imported. Otherwise, you need to rerun the above
  after editing C++ files.")
endif()

if (CMAKE_VERSION VERSION_LESS 3.18)
  set(DEV_MODULE Development)
else()
  set(DEV_MODULE Development.Module)
endif()

find_package(Python 3.10 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Detect the installed nanobind package and import it into CMake
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(
  # Name of the extension
  _core

  NOMINSIZE
  LTO

  # Target the stable ABI for Python 3.12+, which reduces
  # the number of binary wheels that must be built. This
  # does nothing on older Python versions
  STABLE_ABI

  # Source code goes here
  ${BALATRO_GYM_CORE_DIR}/main_module.cpp
  ${BALATRO_GYM_CORE_DIR}/types.cpp
  ${BALATRO_GYM_CORE_DIR}/hand.cpp
  ${BALATRO_GYM_CORE_DIR}/gamestate.cpp
  ${BALATRO_GYM_CORE_DIR}/score.cpp
)

set_property(TARGET _core PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET _core PROPERTY CXX_STANDARD 20)

target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_include_directories(_core PUBLIC)

add_subdirectory(${BALATRO_GYM_CORE_DIR}/balatro)

set_property(TARGET balatro PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET balatro PROPERTY CXX_STANDARD 20)
set_target_properties(balatro PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(_core PRIVATE balatro)


install(TARGETS _core DESTINATION .)
