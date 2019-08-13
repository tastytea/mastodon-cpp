include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)
pkg_check_modules(curlpp REQUIRED IMPORTED_TARGET curlpp)
if(WITH_EASY)
  find_package(jsoncpp REQUIRED CONFIG)
endif()

if(WITH_EASY)
  file(GLOB_RECURSE sources *.cpp *.hpp)
else()
  file(GLOB sources *.cpp api/*.cpp *.hpp api/*.hpp)
endif()

# Write version in header
configure_file ("version.hpp.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.hpp")

add_library(${PROJECT_NAME} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR})

target_include_directories(${PROJECT_NAME}
  PRIVATE
  "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>"
  PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

if(WITH_EASY)
  target_link_libraries(${PROJECT_NAME}
    PUBLIC pthread PkgConfig::curlpp jsoncpp_lib)
else()
  target_link_libraries(${PROJECT_NAME}
    PUBLIC pthread PkgConfig::curlpp)
endif()

install(TARGETS ${PROJECT_NAME}
  EXPORT "${PROJECT_NAME}Targets"
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")

install(FILES mastodon-cpp.hpp return_types.hpp types.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
if(WITH_EASY)
  file(GLOB easy_header easy/*.hpp)
  install(FILES ${easy_header}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/easy)
  file(GLOB easy_entities_header easy/entities/*.hpp)
  install(FILES ${easy_entities_header}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/easy/entities)
endif()
