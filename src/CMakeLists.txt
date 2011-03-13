# Add the executable
ADD_EXECUTABLE(qt_gl
	Camera.cpp
	Light.cpp
	Main.cpp
	Material.cpp
	Mesh.cpp
	Objects.cpp
	QtCore.cpp
	QtWindow.cpp
	QtGlWidget.cpp
	RenderBackend.cpp
	RenderTarget.cpp
	RenderTexture.cpp
	Scene.cpp
	Shader.cpp
	Texture.cpp
	VertexData.cpp
	WorldObject.cpp
	)

# Link against the provided libraries
TARGET_LINK_LIBRARIES(qt_gl
	${QT_LIBRARIES}
	${OPENGL_LIBRARY}
	myglew
	moc
	)

# Add the install targets
INSTALL(TARGETS qt_gl DESTINATION bin)
INSTALL(FILES "${PROJECT_BINARY_DIR}/Config.hpp" DESTINATION include)
