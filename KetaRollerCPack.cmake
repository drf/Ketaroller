INCLUDE(InstallRequiredSystemLibraries)

# Install the shared Qt distribution as well if we're on Windows
if (WIN32)
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        install(FILES ${QT_LIBRARY_DIR}/../bin/QtCore4.dll DESTINATION ${LIB_INSTALL_DIR} COMPONENT mainlibrary)
        install(FILES ${QT_LIBRARY_DIR}/../bin/QtGui4.dll DESTINATION ${LIB_INSTALL_DIR} COMPONENT tuioplugins)
        install(FILES ${QT_LIBRARY_DIR}/../bin/QtTest4.dll DESTINATION ${LIB_INSTALL_DIR} COMPONENT tests)
    else (CMAKE_BUILD_TYPE STREQUAL "Release")
        install(FILES ${QT_LIBRARY_DIR}/../bin/QtCored4.dll DESTINATION ${LIB_INSTALL_DIR} COMPONENT mainlibrary)
        install(FILES ${QT_LIBRARY_DIR}/../bin/QtGuid4.dll DESTINATION ${LIB_INSTALL_DIR} COMPONENT tuioplugins)
        install(FILES ${QT_LIBRARY_DIR}/../bin/QtTestd4.dll DESTINATION ${LIB_INSTALL_DIR} COMPONENT tests)
    endif (CMAKE_BUILD_TYPE STREQUAL "Release")
endif (WIN32)

# Install documentation
if (DOXYGEN_FOUND)
    if (DOXYFILE_PDFLATEX STREQUAL "YES")
        install(FILES ${DOXYFILE_OUTPUT_DIR}/${DOXYFILE_LATEX_DIR}/refman.pdf
                DESTINATION ${DOC_INSTALL_DIR}
                COMPONENT pdfdocumentation)
    endif (DOXYFILE_PDFLATEX STREQUAL "YES")

    file(GLOB ketaroller_html_doc_FILES ${DOXYFILE_OUTPUT_DIR}/${DOXYFILE_HTML_DIR}/*)

    install(FILES ${ketaroller_html_doc_FILES}
            DESTINATION ${HTML_INSTALL_DIR}
            COMPONENT htmldocumentation)
endif (DOXYGEN_FOUND)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An advanced signal router for musical devices")
SET(CPACK_PACKAGE_VENDOR "Dario Freddi, Luca Mucci")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "KetaRoller")
SET(CPACK_PACKAGE_CONTACT "you@you.com")
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
if (DOXYGEN_FOUND)
    if (DOXYFILE_PDFLATEX STREQUAL "YES")
        set(CPACK_COMPONENTS_ALL mainlibrary headers tuioplugins midiplugins tests pdfdocumentation htmldocumentation)
    else (DOXYFILE_PDFLATEX STREQUAL "YES")
        set(CPACK_COMPONENTS_ALL mainlibrary headers tuioplugins midiplugins tests htmldocumentation)
    endif (DOXYFILE_PDFLATEX STREQUAL "YES")
else (DOXYGEN_FOUND)
    set(CPACK_COMPONENTS_ALL mainlibrary headers tuioplugins midiplugins tests)
endif (DOXYGEN_FOUND)

#name components
set(CPACK_COMPONENT_MAINLIBRARY_DISPLAY_NAME "KetaRoller main components")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Development files")
set(CPACK_COMPONENT_TUIOPLUGINS_DISPLAY_NAME "TUIO plugins for KetaRoller")
set(CPACK_COMPONENT_MIDIPLUGINS_DISPLAY_NAME "MIDI plugins for KetaRoller")
set(CPACK_COMPONENT_TESTS_DISPLAY_NAME "Tests and examples")

if (DOXYGEN_FOUND)
    if (DOXYFILE_PDFLATEX STREQUAL "YES")
        set(CPACK_COMPONENT_PDFDOCUMENTATION_DISPLAY_NAME "PDF Reference Manual")
    endif (DOXYFILE_PDFLATEX STREQUAL "YES")

    set(CPACK_COMPONENT_HTMLDOCUMENTATION_DISPLAY_NAME "HTML Reference Manual")
endif (DOXYGEN_FOUND)

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

if (DOXYGEN_FOUND)
    if (DOXYFILE_PDFLATEX STREQUAL "YES")
        set(CPACK_COMPONENT_PDFDOCUMENTATION_DESCRIPTION
            "KetaRoller's reference manual in PDF format")
    endif (DOXYFILE_PDFLATEX STREQUAL "YES")

    set(CPACK_COMPONENT_HTMLDOCUMENTATION_DESCRIPTION
        "KetaRoller's reference manual in HTML format")
endif (DOXYGEN_FOUND)

set(CPACK_COMPONENT_HEADERS_DEPENDS mainlibrary)
set(CPACK_COMPONENT_MIDIPLUGINS_DEPENDS mainlibrary)
set(CPACK_COMPONENT_TUIOPLUGINS_DEPENDS mainlibrary)
set(CPACK_COMPONENT_TESTS_DEPENDS mainlibrary midiplugins tuioplugins)

#groups
set(CPACK_COMPONENT_MIDIPLUGINS_GROUP "Plugins")
set(CPACK_COMPONENT_TUIOPLUGINS_GROUP "Plugins")

if (DOXYGEN_FOUND)
    if (DOXYFILE_PDFLATEX STREQUAL "YES")
        set(CPACK_COMPONENT_PDFDOCUMENTATION_GROUP "Documentation")
    endif (DOXYFILE_PDFLATEX STREQUAL "YES")

    set(CPACK_COMPONENT_HTMLDOCUMENTATION_GROUP "Documentation")
endif (DOXYGEN_FOUND)

#groups description
set(CPACK_COMPONENT_GROUP_PLUGINS_DESCRIPTION
   "Various I/O plugins for KetaRoller")

if (DOXYGEN_FOUND)
    set(CPACK_COMPONENT_GROUP_DOCUMENTATION_DESCRIPTION
        "Reference manual for KetaRoller, including abstracts and API documentation")
endif (DOXYGEN_FOUND)

#installation types
set(CPACK_ALL_INSTALL_TYPES Full User Developer Minimal)

set(CPACK_COMPONENT_MAINLIBRARY_INSTALL_TYPES Full User Developer Minimal)
set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Full Developer)
set(CPACK_COMPONENT_TUIOPLUGINS_INSTALL_TYPES Full User Developer)
set(CPACK_COMPONENT_MIDIPLUGINS_INSTALL_TYPES Full User Developer)
set(CPACK_COMPONENT_TESTS_INSTALL_TYPES Full Developer)

if (DOXYGEN_FOUND)
    if (DOXYFILE_PDFLATEX STREQUAL "YES")
        set(CPACK_COMPONENT_PDFDOCUMENTATION_INSTALL_TYPES Full Developer)
    endif (DOXYFILE_PDFLATEX STREQUAL "YES")

    set(CPACK_COMPONENT_HTMLDOCUMENTATION_INSTALL_TYPES Full Developer)
endif (DOXYGEN_FOUND)

# Leave this as the last declaration, always!!!
include(CPack)
