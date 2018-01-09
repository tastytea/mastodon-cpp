cmake_minimum_required (VERSION 3.7)
project (mastodon-cpp
         VERSION 0.0.1
         LANGUAGES CXX
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

# Write SHA1 hash and date of current git commit to a header file. Also version.
find_package(Git)
if(Git_FOUND)
    # force regeneration of version.hpp on each build
    file(REMOVE "${PROJECT_BINARY_DIR}/version.hpp")
    execute_process(COMMAND "${GIT_EXECUTABLE}" describe --always --abbrev=0 --dirty
                    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
                    OUTPUT_VARIABLE GIT_SHA1
                    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND "${GIT_EXECUTABLE}" log -1 --format=%aI --date=iso-strict
                    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
                    OUTPUT_VARIABLE GIT_DATE
                    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()
include_directories(${MY_SOURCE_DIR}/src)
configure_file (
    "${PROJECT_SOURCE_DIR}/src/version.hpp.in"
    "${PROJECT_BINARY_DIR}/version.hpp"
)
include_directories(${PROJECT_BINARY_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG=1)
endif()

file(GLOB sources src/*.cpp src/*.hpp)
add_library(mastodon-cpp SHARED ${sources})
set_target_properties(mastodon-cpp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${mastodon-cpp_VERSION_MAJOR}
)
install(TARGETS mastodon-cpp DESTINATION lib)
target_link_libraries(mastodon-cpp pthread boost_system ssl crypto)
install(FILES ${PROJECT_SOURCE_DIR}/src/lib/mastodon-cpp.hpp DESTINATION include)

# Example client
if(NOT LIB_ONLY)
    file(GLOB_RECURSE sources_example src/example/*.cpp)
    add_executable(example ${sources_example})
    target_link_libraries(example mastodon-cpp)
endif()

# Tests
if(NOT NOTESTS)
    include(CTest)
    file(GLOB sources_tests "src/tests/test_*.cpp")
    foreach(src ${sources_tests})
        get_filename_component(bin ${src} NAME_WE)
        add_executable(${bin} ${src})
        target_link_libraries(${bin} mastodon-cpp)
        add_test(${bin} ${bin})
    endforeach()
endif()
