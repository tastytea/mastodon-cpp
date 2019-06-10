cmake_minimum_required (VERSION 3.6)
project (mastodon-cpp
  VERSION 0.105.1
  LANGUAGES CXX
  )

set(WITH_EASY "YES" CACHE STRING "WITH_EASY defaults to \"YES\"")
set(WITH_EXAMPLES "NO" CACHE STRING "WITH_EXAMPLES defaults to \"NO\"")
set(WITH_TESTS "NO" CACHE STRING "WITH_TESTS defaults to \"NO\"")
set(WITH_DOC "YES" CACHE STRING "WITH_DOC defaults to \"YES\"")
set(WITH_DEB "NO" CACHE STRING "WITH_DEB defaults to \"NO\"")
set(WITH_RPM "NO" CACHE STRING "WITH_RPM defaults to \"NO\"")

include(GNUInstallDirs)
find_package(PkgConfig REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CURLPP REQUIRED curlpp)
if(WITH_EASY)
  pkg_check_modules(JSONCPP REQUIRED jsoncpp)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG
  "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wpedantic -ftrapv -fsanitize=undefined -g -Og -fno-omit-frame-pointer")

# Do not complain about compatibility-wrapper
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
endif()

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR})

include_directories(${CURL_INCLUDE_DIRS})
include_directories(${CURLPP_INCLUDE_DIRS})
include_directories(${JSONCPP_INCLUDE_DIRS})

link_directories(${CURL_LIBRARY_DIRS})
link_directories(${CURLPP_LIBRARY_DIRS})
link_directories(${JSONCPP_LIBRARY_DIRS})

# Write version in header
configure_file (
  "${PROJECT_SOURCE_DIR}/src/version.hpp.in"
  "${PROJECT_BINARY_DIR}/version.hpp"
)

# Announce that we are compiling mastodon-cpp (used to figure out where the
# headers are)
add_definitions(-DMASTODON_CPP=1)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG=1)
endif()

if(NOT WITH_EASY)
  add_definitions(-DWITHOUT_EASY=1)
endif()

# Compile library
if(WITH_EASY)
  file(GLOB sources src/*.cpp src/api/*.cpp
    src/easy/*.cpp src/easy/entities/*.cpp)
else()
  file(GLOB sources src/*.cpp src/api/*.cpp)
endif()
add_library(${PROJECT_NAME} SHARED ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}
  )

if(WITH_EASY)
  target_link_libraries(${PROJECT_NAME}
    ${CURLPP_LIBRARIES} pthread ${JSONCPP_LIBRARIES})
else()
  target_link_libraries(${PROJECT_NAME}
    ${CURLPP_LIBRARIES} pthread)
endif()

# Compile examples
if(WITH_EXAMPLES)
  file(GLOB sources_examples examples/*.cpp)
  foreach(src ${sources_examples})
    get_filename_component(bin ${src} NAME_WE)
    add_executable(${bin} ${src})
    target_link_libraries(${bin} pthread ${JSONCPP_LIBRARIES} ${PROJECT_NAME})
  endforeach()
endif()

# Compile tests
if(WITH_TESTS)
  configure_file("tests/test.gif" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
  add_subdirectory(tests)
endif()

# Install library and header files
install(TARGETS ${PROJECT_NAME} LIBRARY
  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES src/mastodon-cpp.hpp src/return_types.hpp src/types.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
if(WITH_EASY)
  file(GLOB easy_header src/easy/*.hpp)
  install(FILES ${easy_header}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/easy)
  file(GLOB easy_entities_header src/easy/entities/*.hpp)
  install(FILES ${easy_entities_header}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/easy/entities)
endif()

# Compile & install documentation
if(WITH_DOC)
  add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/doc/html
    COMMAND ./build_doc.sh WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  add_custom_target(doc DEPENDS doc/html)
  add_dependencies(${PROJECT_NAME} doc)
  install(DIRECTORY ${PROJECT_SOURCE_DIR}/doc/html
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME}-${PROJECT_VERSION})
  file(GLOB examples examples/example*.cpp)
  install(FILES ${examples}
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME}-${PROJECT_VERSION}/examples)
endif()

# Packages
include(packages.CMakeLists.txt)
