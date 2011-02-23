# Add the glew library
ADD_LIBRARY(myglew
	glew/src/glew.c
	)

# Link against the provided libraries
TARGET_LINK_LIBRARIES(myglew
	${OPENGL_LIBRARY}
	)
