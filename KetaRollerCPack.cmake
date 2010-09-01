INCLUDE(InstallRequiredSystemLibraries)

# Install the shared Qt distribution as well if we're on Windows
if (WIN32)
    install(FILES ${QT_QTCORE_LIBRARY} DESTINATION ${LIB_INSTALL_DIR} COMPONENT mainlibrary)
    install(FILES ${QT_QTGUI_LIBRARY} DESTINATION ${LIB_INSTALL_DIR} COMPONENT tuioplugins)
    install(FILES ${QT_QTTEST_LIBRARY} DESTINATION ${LIB_INSTALL_DIR} COMPONENT tests)
endif (WIN32)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An advanced signal router for musical devices")
SET(CPACK_PACKAGE_VENDOR "Dario Freddi, Luca Mucci")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "KetaRoller")
set(CPACK_SOURCE_IGNORE_FILES
   "/build/;/.bzr/;~$;/.git/;/.kdev4/;/installatio/;${CPACK_SOURCE_IGNORE_FILES}")
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  #SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
  #SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} KetaRoller")
  #SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.github.com")
  #SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
  #SET(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  #SET(CPACK_STRIP_FILES "bin/MyExecutable")
  SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
#SET(CPACK_PACKAGE_EXECUTABLES "MyExecutable" "My Executable")

if (APPLE)
    set(CPACK_SET_DESTDIR ON)
    set(CPACK_PACKAGE_RELOCATABLE OFF)
endif (APPLE)

#define components
set(CPACK_COMPONENTS_ALL mainlibrary headers tuioplugins midiplugins tests)

#name components
set(CPACK_COMPONENT_MAINLIBRARY_DISPLAY_NAME "KetaRoller main components")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Development files")
set(CPACK_COMPONENT_TUIOPLUGINS_DISPLAY_NAME "TUIO plugins for KetaRoller")
set(CPACK_COMPONENT_MIDIPLUGINS_DISPLAY_NAME "MIDI plugins for KetaRoller")
set(CPACK_COMPONENT_TESTS_DISPLAY_NAME "Tests and examples")

#components description
set(CPACK_COMPONENT_MAINLIBRARY_DESCRIPTION
   "The main KetaRoller library and its dependencies")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION
   "Header files for KetaRoller - needed if you need to create your own plugin and/or application")
set(CPACK_COMPONENT_TUIOPLUGINS_DESCRIPTION
   "TUIO i/o support for KetaRoller")
set(CPACK_COMPONENT_MIDIPLUGINS_DESCRIPTION
   "MIDI i/o support for KetaRoller")
set(CPACK_COMPONENT_TESTS_DESCRIPTION
   "A set of small application to test KetaRoller's functionalities")

set(CPACK_COMPONENT_HEADERS_DEPENDS mainlibrary)
set(CPACK_COMPONENT_MIDIPLUGINS_DEPENDS mainlibrary)
set(CPACK_COMPONENT_TUIOPLUGINS_DEPENDS mainlibrary)
set(CPACK_COMPONENT_TESTS_DEPENDS mainlibrary midiplugins tuioplugins)

#groups
set(CPACK_COMPONENT_MIDIPLUGINS_GROUP "Plugins")
set(CPACK_COMPONENT_TUIOPLUGINS_GROUP "Plugins")

#groups description
set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION
   "Various I/O plugins for KetaRoller")

#installation types
set(CPACK_ALL_INSTALL_TYPES Full User Developer Minimal)

set(CPACK_COMPONENT_MAINLIBRARY_INSTALL_TYPES Full User Developer Minimal)
set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Full Developer)
set(CPACK_COMPONENT_TUIOPLUGINS_INSTALL_TYPES Full User Developer)
set(CPACK_COMPONENT_MIDIPLUGINS_INSTALL_TYPES Full User Developer)
set(CPACK_COMPONENT_MAINLIBRARY_INSTALL_TYPES Full Developer)

# Leave this as the last declaration, always!!!
include(CPack)
