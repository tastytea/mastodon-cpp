cmake_minimum_required (VERSION 3.7)
project (mastodon-cpp
         VERSION 0.1.1
         LANGUAGES CXX
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

# Write version in header
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
target_link_libraries(mastodon-cpp boost_system ssl crypto)
install(FILES ${PROJECT_SOURCE_DIR}/src/mastodon-cpp.hpp DESTINATION include)

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
