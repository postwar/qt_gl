CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(QtGlTest)

# Version number
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 1)
SET(VERSION_PATCH 0)

# Add path for CMake modules
SET(CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_DIR}")

# Required options
SET(CMAKE_REQUIRED_LIBRARIES)
SET(QT_USE_QTOPENGL TRUE)

# Required packages
FIND_PACKAGE(Qt4 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

# Configure a header file to pass some of the CMake settings to the source code
CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/Config.hpp.in"
	"${PROJECT_BINARY_DIR}/Config.hpp"
	)


# Add the binary tree to the search path for include files so that we will find
# Config.hpp
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
# Add the include directory
INCLUDE_DIRECTORIES("include")

INCLUDE(${QT_USE_FILE})

# Set the compiler and linker flags
#ADD_DEFINITIONS(-g -O2 -Wall -Wextra -pedantic -Werror -W
#	-Wpointer-arith -Wcast-qual -Winline -fsigned-char -freg-struct-return
#	)
ADD_DEFINITIONS(-g -O2 -Wall -Wextra)
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DGL_GLEXT_PROTOTYPES)
ADD_DEFINITIONS(-DGLEW_STATIC)

# Directories that are built recursively
ADD_SUBDIRECTORY(include)
ADD_SUBDIRECTORY(ext)
ADD_SUBDIRECTORY(src)

# Documentation files
SET(DOC_FILES AUTHORS ChangeLog COPYING NEWS README)
SET(DOC_PATH "share/doc/qt_gl")
INSTALL(FILES ${DOC_FILES} DESTINATION ${DOC_PATH})

# Create a "dist" target which updates the CMake cache and replaces the
# package_source target for easy/intuitive use
ADD_CUSTOM_TARGET(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
ADD_CUSTOM_TARGET(pack COMMAND cpack)

# Status messages
MESSAGE(STATUS)
MESSAGE(STATUS "Change a value with: cmake -D<Variable>=<Value>")
MESSAGE(STATUS)

# Build a CPack driven installer package
INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Qt framework test with OpenGL")
SET(CPACK_PACKAGE_CONTACT "Sven Schneider")
SET(CPACK_PACKAGE_VENDOR "Sven Schneider")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")

SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
SET(VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${VERSION}")

#SET(CPACK_GENERATOR "DEB;RPM;")
SET(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}-${CMAKE_SYSTEM_PROCESSOR}")

SET(CPACK_SOURCE_IGNORE_FILES "/build/;/.git/;/.svn/;/.bzr/;~$;${CPACK_SOURCE_IGNORE_FILES}")

INCLUDE(CPack)
