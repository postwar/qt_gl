SET(MOC_HEADER_FILES
	QtCore.hpp
	QtGlWidget.hpp
	QtWindow.hpp
	)

SET(HEADERS
	${MOC_HEADERS}
	Camera.hpp
	Rectangle.hpp
	RenderBackend.hpp
	RenderData.hpp
	)

INSTALL(FILES
	HEADERS
	DESTINATION include)

# Pre-compile the Qt headers
QT_WRAP_CPP(moc MOC_SOURCE_FILES ${MOC_HEADER_FILES})

ADD_LIBRARY(moc ${MOC_SOURCE_FILES})
TARGET_LINK_LIBRARIES(moc
	${QT_LIBRARIES}
	)
