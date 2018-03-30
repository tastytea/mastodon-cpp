cmake_minimum_required (VERSION 3.7)
project (mastodon-cpp
         VERSION 0.7.9
         LANGUAGES CXX
)

include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set(CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR})

# Write version in header
configure_file (
    "${PROJECT_SOURCE_DIR}/src/version.hpp.in"
    "${PROJECT_BINARY_DIR}/version.hpp"
)

# Announce that we are compiling mastodon-cpp (used in easy.hpp and examples)
add_definitions(-DMASTODON_CPP=1)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG=1)
endif()

if(WITHOUT_EASY)
    add_definitions(-DWITHOUT_EASY=1)
endif()

# Library
if(WITHOUT_EASY)
    file(GLOB sources src/*.cpp src/api/*.cpp)
else()
    file(GLOB sources src/*.cpp src/api/*.cpp src/easy/*.cpp)
endif()
add_library(mastodon-cpp SHARED ${sources})
set_target_properties(mastodon-cpp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${mastodon-cpp_VERSION_MAJOR}
)
if(WITHOUT_EASY)
    target_link_libraries(mastodon-cpp curlpp)
else()
    target_link_libraries(mastodon-cpp curlpp jsoncpp)
endif()
install(TARGETS mastodon-cpp LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES src/mastodon-cpp.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mastodon-cpp)
if(NOT WITHOUT_EASY)
    file(GLOB easy_header src/easy/*.hpp)
    list(FILTER easy_header EXCLUDE REGEX "easy\.hpp$")
    install(FILES src/easy/easy.hpp
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mastodon-cpp)
    install(FILES ${easy_header}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mastodon-cpp/easy)
endif()

# Documentation
if(WITH_DOC)
    execute_process(COMMAND ./build_doc.sh
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/doc/html
            DESTINATION ${CMAKE_INSTALL_DOCDIR}/mastodon-cpp-${PROJECT_VERSION})
    file(GLOB examples src/examples/example*.cpp)
    install(FILES ${examples}
            DESTINATION ${CMAKE_INSTALL_DOCDIR}/mastodon-cpp-${PROJECT_VERSION}/examples)
endif()

# Examples
if(WITH_EXAMPLES)
    file(GLOB sources_examples examples/*.cpp)
    foreach(src ${sources_examples})
        get_filename_component(bin ${src} NAME_WE)
        add_executable(${bin} ${src})
        target_link_libraries(${bin} pthread jsoncpp mastodon-cpp)
    endforeach()
endif()

# Tests
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
set(CPACK_SOURCE_PACKAGE_FILE_NAME, "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_IGNORE_FILES, "/\\\\.git/;/build/;/doc/;.\\\\.sublime-")
set(CPACK_GENERATOR "TGZ")

if (WITH_DEB)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/tastytea/mastodon-cpp")
    #set(CPACK_DEBIAN_PACKAGE_DEPENDS "libcurlpp0 (>= 0.7.3)")
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    execute_process(COMMAND dpkg --print-architecture
                    OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(CPACK_PACKAGE_FILE_NAME
         "lib${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-0_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
endif()

if (WITH_RPM)
    set(CPACK_GENERATOR "RPM")
    set(CPACK_RPM_PACKAGE_LICENSE "GPL-3")
    set(CPACK_RPM_PACKAGE_URL "https://github.com/tastytea/mastodon-cpp")
    set(CPACK_RPM_PACKAGE_REQUIRES "curlpp >= 0.7.3")
    execute_process(COMMAND uname -m
                    OUTPUT_VARIABLE CPACK_RPM_PACKAGE_ARCHITECTURE
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(CPACK_PACKAGE_FILE_NAME
         "lib${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-0.${CPACK_RPM_PACKAGE_ARCHITECTURE}")
endif()

include(CPack)
