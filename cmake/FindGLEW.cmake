# Adpated from nvidia-texture-tools
# http://code.google.com/p/nvidia-texture-tools/

#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_PATH
# GLEW_LIBRARY
# 

IF (WIN32)
	FIND_PATH(GLEW_INCLUDE_PATH
		NAMES GL/glew.h
		PATHS
		C:/mingw
		C:/programme/mingw
		$ENV{PROGRAMFILES}/GLEW/include
		DOC "The directory where GL/glew.h resides"
	)
	FIND_LIBRARY(GLEW_LIBRARY
		NAMES glew GLEW glew32 glew32s
		PATH_SUFFIXES lib
		PATHS
		C:/mingw
		C:/programme/mingw
		$ENV{PROGRAMFILES}/GLEW/lib
		DOC "The GLEW library"
	)
ELSE (WIN32)
	FIND_PATH(GLEW_INCLUDE_PATH GL/glew.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where GL/glew.h resides"
	)
	FIND_LIBRARY(GLEW_LIBRARY
		NAMES GLEW glew
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The GLEW library"
	)
ENDIF (WIN32)

IF (GLEW_INCLUDE_PATH)
	SET(GLEW_FOUND 1 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ELSE (GLEW_INCLUDE_PATH)
	SET(GLEW_FOUND 0 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ENDIF (GLEW_INCLUDE_PATH)

MARK_AS_ADVANCED(GLEW_FOUND)

