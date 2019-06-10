include(CTest)
file(GLOB sources_tests test_*.cpp */test_*.cpp)

find_package(Catch2)
if(Catch2_FOUND)    # Catch 2.x
  include(Catch)
  add_executable(all_tests main.cpp ${sources_tests})
  target_link_libraries(all_tests ${PROJECT_NAME} Catch2::Catch2)
  target_include_directories(all_tests PRIVATE "/usr/include/catch2")
  catch_discover_tests(all_tests EXTRA_ARGS "${EXTRA_TEST_ARGS}")
else()              # Catch 1.x
  if(EXISTS "/usr/include/catch.hpp")
    message(STATUS "Catch 1.x found.")
    foreach(src ${sources_tests})
      get_filename_component(bin ${src} NAME_WE)
      add_executable(${bin} tests/main.cpp ${src})
      target_link_libraries(${bin} ${PROJECT_NAME})
      add_test(${bin} ${bin} "${EXTRA_TEST_ARGS}")
    endforeach()
  else()
    message(FATAL_ERROR
      "Neither Catch 2.x nor Catch 1.x could be found.")
  endif()
endif()
