set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${mastodon-cpp_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_CONTACT "tastytea <tastytea@tastytea.de>")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.adoc")

execute_process(COMMAND uname -m
  OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CPACK_PACKAGE_FILE_NAME
  "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}_${CPACK_PACKAGE_ARCHITECTURE}")
set(CPACK_GENERATOR "TGZ")

if (WITH_DEB)
  set(CPACK_PACKAGE_NAME "lib${PROJECT_NAME}")
  set(CPACK_GENERATOR "DEB")
  set(CPACK_DEBIAN_PACKAGE_HOMEPAGE
    "https://schlomp.space/tastytea/${PROJECT_NAME}")
  set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
  execute_process(COMMAND dpkg --print-architecture
    OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-0_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
endif()

if (WITH_RPM)
  set(CPACK_PACKAGE_NAME "lib${PROJECT_NAME}")
  set(CPACK_GENERATOR "RPM")
  set(CPACK_RPM_PACKAGE_LICENSE "AGPL-3")
  set(CPACK_RPM_PACKAGE_URL "https://schlomp.space/tastytea/${PROJECT_NAME}")
  set(CPACK_RPM_PACKAGE_REQUIRES "curlpp >= 0.8.1 jsoncpp, >= 1.7.4")
  set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-0.${CPACK_PACKAGE_ARCHITECTURE}")
endif()

include(CPack)
