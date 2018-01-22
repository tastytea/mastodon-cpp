cmake_minimum_required (VERSION 3.7)
include(GNUInstallDirs)

project (mastodon-cpp
         VERSION 0.1.4
         LANGUAGES CXX
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

include_directories(${MY_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR})

# Write version in header
configure_file (
    "${PROJECT_SOURCE_DIR}/src/version.hpp.in"
    "${PROJECT_BINARY_DIR}/version.hpp"
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG=1)
endif()

# Library
file(GLOB sources src/*.cpp src/*.hpp)
add_library(mastodon-cpp SHARED ${sources})
set_target_properties(mastodon-cpp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${mastodon-cpp_VERSION_MAJOR}
)
target_link_libraries(mastodon-cpp boost_system ssl crypto)
install(TARGETS mastodon-cpp LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${PROJECT_SOURCE_DIR}/src/mastodon-cpp.hpp
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Documentation
if(WITH_DOC)
    execute_process(COMMAND ./build_doc.sh
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/doc/html
            DESTINATION ${CMAKE_INSTALL_DOCDIR}/mastodon-cpp-${PROJECT_VERSION})
    install(FILES ${PROJECT_SOURCE_DIR}/src/examples/example.cpp
            DESTINATION ${CMAKE_INSTALL_DOCDIR}/mastodon-cpp-${PROJECT_VERSION}/examples)
endif()

# Examples
if(WITH_EXAMPLES)
    file(GLOB sources_examples src/examples/*.cpp)
    foreach(src ${sources_examples})
        get_filename_component(bin ${src} NAME_WE)
        add_executable(${bin} ${src})
        target_link_libraries(${bin} mastodon-cpp)
    endforeach()
endif()

# Tests
if(WITH_TESTS)
    include(CTest)
    file(GLOB sources_tests src/tests/test_*.cpp)
    foreach(src ${sources_tests})
        get_filename_component(bin ${src} NAME_WE)
        add_executable(${bin} ${src})
        target_link_libraries(${bin} mastodon-cpp)
        add_test(${bin} ${bin})
    endforeach()
endif()
