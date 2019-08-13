file(GLOB sources_examples *.cpp)
foreach(src ${sources_examples})
  get_filename_component(bin ${src} NAME_WE)
  add_executable(${bin} ${src})
  target_link_libraries(${bin} PRIVATE ${PROJECT_NAME})
endforeach()

if(WITH_DOC)
  install(FILES ${sources_examples}
    DESTINATION "${CMAKE_INSTALL_DOCDIR}/examples")
endif()
