cmake_minimum_required (VERSION 3.6)
project (mastodon-cpp
         VERSION 0.20.0
         LANGUAGES CXX
)

include(GNUInstallDirs)
find_package(PkgConfig REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CURLPP REQUIRED curlpp)
if(NOT WITHOUT_EASY)
    pkg_check_modules(JSONCPP REQUIRED jsoncpp)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -Og")

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

if(WITHOUT_EASY)
    add_definitions(-DWITHOUT_EASY=1)
endif()

# Compile library
if(WITHOUT_EASY)
    file(GLOB sources src/*.cpp src/api/*.cpp)
else()
    file(GLOB sources src/*.cpp src/api/*.cpp
                      src/easy/*.cpp src/easy/entities/*.cpp)
endif()
add_library(mastodon-cpp SHARED ${sources})
set_target_properties(mastodon-cpp PROPERTIES
                     VERSION ${PROJECT_VERSION}
                     SOVERSION ${mastodon-cpp_VERSION_MAJOR}
)

if(WITHOUT_EASY)
    target_link_libraries(mastodon-cpp ${CURLPP_LIBRARIES})
else()
    target_link_libraries(mastodon-cpp ${CURLPP_LIBRARIES} ${JSONCPP_LIBRARIES})
endif()

if(WITH_STATIC)
    add_library(mastodon-cpp_static STATIC ${sources})
    set_target_properties(mastodon-cpp_static PROPERTIES
                          OUTPUT_NAME mastodon-cpp)
endif()

# Compile examples
if(WITH_EXAMPLES)
    file(GLOB sources_examples examples/*.cpp)
    foreach(src ${sources_examples})
        get_filename_component(bin ${src} NAME_WE)
        add_executable(${bin} ${src})
        target_link_libraries(${bin} pthread ${JSONCPP_LIBRARIES} mastodon-cpp)
    endforeach()
endif()

# Compile tests
if(WITH_TESTS)
    include(CTest)
    file(GLOB sources_tests tests/test_*.cpp)
    foreach(src ${sources_tests})
        get_filename_component(bin ${src} NAME_WE)
        add_executable(${bin} ${src})
        target_link_libraries(${bin} mastodon-cpp)
        add_test(${bin} ${bin})
    endforeach()
endif()

# Install library and header files
install(TARGETS mastodon-cpp LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
if(WITH_STATIC)
    install(TARGETS mastodon-cpp_static LIBRARY
            DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
install(FILES src/mastodon-cpp.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mastodon-cpp)
if(NOT WITHOUT_EASY)
    file(GLOB easy_header src/easy/*.hpp)
    install(FILES ${easy_header}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mastodon-cpp/easy)
    file(GLOB easy_entities_header src/easy/entities/*.hpp)
    install(FILES ${easy_entities_header}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mastodon-cpp/easy/entities)
endif()

# Compile & install documentation
if(WITH_DOC)
    execute_process(COMMAND ./build_doc.sh
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/doc/html
            DESTINATION ${CMAKE_INSTALL_DOCDIR}/mastodon-cpp-${PROJECT_VERSION})
    file(GLOB examples examples/example*.cpp)
    install(FILES ${examples}
            DESTINATION ${CMAKE_INSTALL_DOCDIR}/mastodon-cpp-${PROJECT_VERSION}/examples)
endif()

# Packages
set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${mastodon-cpp_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${mastodon-cpp_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${mastodon-cpp_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${mastodon-cpp_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ wrapper for the Mastodon API")
set(CPACK_PACKAGE_CONTACT "tastytea <tastytea@tastytea.de>")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")
list(APPEND CPACK_SOURCE_IGNORE_FILES "/\\\\.git"
                                      "/.gitignore"
                                      "/build/"
                                      "/doc/"
                                      "\\\\.sublime-"
                                      "/update_doc.sh"
                                      "/.drone.yml"
                                      "/ISSUE_TEMPLATE.md$")
execute_process(COMMAND uname -m
                OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE
                OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}_${CPACK_PACKAGE_ARCHITECTURE}")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")

if (WITH_DEB)
    set(CPACK_PACKAGE_NAME "lib${CMAKE_PROJECT_NAME}")
    set(CPACK_GENERATOR "DEB")
    set(CPACK_SOURCE_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://schlomp.space/tastytea/mastodon-cpp")
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    execute_process(COMMAND dpkg --print-architecture
                    OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(CPACK_PACKAGE_FILE_NAME
        "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-0_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
    set(CPACK_SOURCE_PACKAGE_FILE_NAME
        "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-0_src")
endif()

if (WITH_RPM)
    set(CPACK_PACKAGE_NAME "lib${CMAKE_PROJECT_NAME}")
    set(CPACK_GENERATOR "RPM")
    set(CPACK_SOURCE_GENERATOR "RPM")
    set(CPACK_RPM_PACKAGE_LICENSE "GPL-3")
    set(CPACK_RPM_PACKAGE_URL "https://schlomp.space/tastytea/mastodon-cpp")
    set(CPACK_RPM_PACKAGE_REQUIRES "curlpp >= 0.8.1 jsoncpp, >= 1.7.4")
    set(CPACK_PACKAGE_FILE_NAME
         "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-0.${CPACK_PACKAGE_ARCHITECTURE}")
    set(CPACK_SOURCE_PACKAGE_FILE_NAME
        "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-0.src")
endif()

include(CPack)
