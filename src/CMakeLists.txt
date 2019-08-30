include(GNUInstallDirs)

if(WITH_EASY)
  find_package(jsoncpp CONFIG REQUIRED)
endif()
# Some distributions do not contain Poco*Config.cmake recipes.
find_package(Poco COMPONENTS Foundation Net NetSSL CONFIG)

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
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
  PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

if(WITH_EASY)
  target_link_libraries(${PROJECT_NAME}
    PUBLIC pthread jsoncpp_lib)
endif()

# If no Poco*Config.cmake recipes are found, look for headers in standard dirs.
if(PocoNetSSL_FOUND)
  target_link_libraries(${PROJECT_NAME}
    PRIVATE Poco::Foundation Poco::Net Poco::NetSSL)
else()
  find_file(Poco_h NAMES "Poco/Poco.h"
    PATHS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")

  if("${Poco_h}" STREQUAL "Poco_h-NOTFOUND")
    message(FATAL_ERROR "Could not find POCO.")
  else()
    message(WARNING
      "Your distribution of POCO doesn't contain the *Config.cmake recipes, "
      "but the files seem to be in the standard directories. "
      "Let's hope this works.")
    target_link_libraries(${PROJECT_NAME}
      PRIVATE PocoFoundation PocoNet PocoNetSSL)
  endif()
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
