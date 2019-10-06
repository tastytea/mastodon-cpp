# Support version 3.6 and above, but use policy settings up to 3.14.
# 3.6 is needed because of IMPORTED_TARGET in pkg_check_modules().
cmake_minimum_required(VERSION 3.6...3.14)
# Ranges are supported from 3.12, set policy to current for < 3.12.
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

include(GNUInstallDirs)

project (mastodon-cpp
  VERSION 0.111.1
  LANGUAGES CXX)

# DESCRIPTION was introduced in version 3.9.
if(NOT (${CMAKE_VERSION} VERSION_LESS 3.9))
  set(PROJECT_DESCRIPTION
    "C++ wrapper for the Mastodon API.")
endif()

option(WITH_EASY "Compile Easy interface." YES)
option(WITH_EXAMPLES "Compile examples." NO)
option(WITH_TESTS "Compile tests." NO)
option(WITH_DOC "Generate HTML documentation." YES)
option(WITH_DEB "Prepare for the building of .deb packages." NO)
option(WITH_RPM "Prepare for the building of .rpm packages." NO)
option(BUILD_SHARED_LIBS "Build shared libraries." YES)
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type, Release or Debug.")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DEBUG_CXXFLAGS
  "-Wall"
  "-Wextra"
  "-Wpedantic"
  "-ftrapv"
  "-fsanitize=undefined"
  "-g"
  "-Og"
  "-fno-omit-frame-pointer"
  "-Wno-deprecated-declarations")
set(DEBUG_LDFLAGS
  "-fsanitize=undefined")
add_compile_options("$<$<CONFIG:Debug>:${DEBUG_CXXFLAGS}>")
# add_link_options was introduced in version 3.13.
if(${CMAKE_VERSION} VERSION_LESS 3.13)
  set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${DEBUG_LDFLAGS}")
else()
  add_link_options("$<$<CONFIG:Debug>:${DEBUG_LDFLAGS}>")
endif()

# Turn on debug output.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions("-DDEBUG=1")
endif()

if(NOT WITH_EASY)
  add_definitions("-DWITHOUT_EASY=1")
endif()

add_subdirectory("src")

if(WITH_EXAMPLES)
  add_subdirectory("examples")
endif()

if(WITH_TESTS)
  add_subdirectory("tests")
endif()

if(WITH_DOC)
  add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/doc/html
    COMMAND "./build_doc.sh" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  add_custom_target(doc DEPENDS doc/html)
  add_dependencies(${PROJECT_NAME} doc)

  install(DIRECTORY ${PROJECT_SOURCE_DIR}/doc/html
    DESTINATION "${CMAKE_INSTALL_DOCDIR}/${PROJECT_NAME}")
endif()

add_subdirectory("cmake")
add_subdirectory("pkg-config")

include("cmake/packages.cmake")
