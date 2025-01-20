cmake_minimum_required(VERSION 3.16)
project(MyFLTKProject)

# https://github.com/fltk/fltk/blob/master/README.CMake.txt
set(FLTK_USE_SYSTEM_LIBPNG OFF)
set(FLTK_USE_SYSTEM_ZLIB OFF)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add FLTK as a subdirectory, but exclude its targets
add_subdirectory(third_party/fltk EXCLUDE_FROM_ALL)

# Add the source files
add_executable(MyPortableApp src/main.cpp)

# Link FLTK to the project
target_link_libraries(MyPortableApp PRIVATE fltk fltk_images fltk_jpeg fltk_png fltk_z)


# Enable CPack variables
install(TARGETS MyPortableApp RUNTIME DESTINATION bin )
# General package settings
set(CPACK_PACKAGE_NAME "MyPortableApp")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "Tadej Panjtar <tadej.panjtar@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A portable application example")
set(CPACK_PACKAGE_VENDOR "MyCompany")
set(CPACK_PACKAGE_LICENSE "MIT")
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

# Platform-specific settings
if(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_BUNDLE_NAME "MyPortableApp")
#    set(CPACK_BUNDLE_ICON "${CMAKE_SOURCE_DIR}/icon.icns")
#    set(CPACK_BUNDLE_PLIST "${CMAKE_SOURCE_DIR}/Info.plist")
    set(CPACK_BUNDLE_STARTUP_COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MyPortableApp")
elseif(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_DISPLAY_NAME "My Portable App")
    set(CPACK_NSIS_HELP_LINK "http://example.com/help")
    set(CPACK_NSIS_URL_INFO_ABOUT "http://example.com/about")
elseif(UNIX)
    set(CPACK_GENERATOR "DEB;TGZ")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Tadej Panjtar")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.27)")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")
endif()

# Include CPack module to generate the package
include(CPack)

