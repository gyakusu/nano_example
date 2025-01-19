cmake_minimum_required(VERSION 3.15...3.26)

project(nanoDBRAIN LANGUAGES CXX)

if (NOT SKBUILD)
  message(WARNING "\
  This CMake file is meant to be executed using 'scikit-build'. Running
  it directly will almost certainly not produce the desired result. If
  you are a user trying to install this package, please use the command
  below, which will install all necessary build dependencies, compile
  the package in an isolated environment, and then install it.
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
  the package is imported. Otherwise, you need to re-run the above
  after editing C++ files.")
endif()

# Try to import all Python components potentially needed by nanobind
find_package(Python 3.8
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule)

# Import nanobind through CMake's find_package mechanism
find_package(nanobind CONFIG REQUIRED)

# add this line to use DBRAIN
#
find_package(Eigen3 REQUIRED)
message("-- Found Eigen version ${Eigen3_VERSION}: ${Eigen3_DIR} and include by ${EIGEN3_INCLUDE_DIR}")
include_directories(GLOB_RECURSE "../include")
file(GLOB_RECURSE LIB_SUB "../src/sub.cpp")
add_library(SUB STATIC ${LIB_SUB})
target_link_libraries(SUB PUBLIC Eigen3::Eigen)
set_target_properties(SUB PROPERTIES POSITION_INDEPENDENT_CODE ON)
message("-- Include directory: ${CMAKE_CURRENT_SOURCE_DIR}/../include/")
#
# end of line to use DBRAIN

# We are now ready to compile the actual extension module
nanobind_add_module(
  # Name of the extension
  nanoDBRAIN_ext

  # Target the stable ABI for Python 3.12+, which reduces
  # the number of binary wheels that must be built. This
  # does nothing on older Python versions
  STABLE_ABI

  # Build libnanobind statically and merge it into the
  # extension (which itself remains a shared library)
  #
  # If your project builds multiple extensions, you can
  # replace this flag by NB_SHARED to conserve space by
  # reusing a shared libnanobind across libraries
  NB_STATIC

  # Source code goes here
  src/nanoDBRAIN_ext.cpp
)

target_link_libraries(
  nanoDBRAIN_ext 
  PUBLIC 
  SUB
  Eigen3::Eigen
  )

# Install directive for scikit-build-core
install(TARGETS nanoDBRAIN_ext LIBRARY DESTINATION nanoDBRAIN)
