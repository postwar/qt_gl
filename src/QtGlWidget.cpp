#include "QtGlWidget.hpp"
#include <iostream>
#include <QtGui/QMouseEvent>


QtGlWidget::QtGlWidget(QGLFormat format, QWidget *parent)
		// We need the alpha channel for the color picking
		: QGLWidget(format, parent) {
	// showFullScreen();
	
	// always emit mouse movement events
	setMouseTracking(true);
	
	gettimeofday(&m_LastUpdate, NULL);
	m_FrameRate = 0.0;
}


QtGlWidget::~QtGlWidget() {
}


void QtGlWidget::Update() {
	m_RenderBackend.StartFrame();
	
	m_Scene.Update();
	
	const std::vector<WorldObject> &data = m_Scene.GetRenderData();
	for (unsigned int i = 0; i < data.size(); i++) {
		m_RenderBackend.PushRenderData(data[i]);
	}
	
	const std::vector<Camera> &cameras = m_Scene.GetCameras();
	for (unsigned int i = 0; i < cameras.size(); i++) {
		m_RenderBackend.PushCamera(cameras[i]);
	}
	
	updateGL();
	
	CalculateFrameRate();
    std::cout << "FPS: " << m_FrameRate << std::endl;
    
	m_RenderBackend.EndFrame();
}


QSize QtGlWidget::minimumSizeHint() const {
	return QSize(50, 50);
}


QSize QtGlWidget::sizeHint() const {
	return QSize(800, 600);
}


void QtGlWidget::initializeGL() {
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "GLEW initialization failed: " << std::endl;
		std::cerr << "\t" << glewGetErrorString(err) << std::endl;
	} else {
		std::cout << "GLEW initialization successful" << std::endl;
	}
	
	m_Scene.Initialize();
	m_RenderBackend.Initialize();
}


void QtGlWidget::paintGL() {
	// m_RenderBackend.RenderSelect();
	m_RenderBackend.Render();
}


void QtGlWidget::resizeGL(int width, int height) {
	m_Scene.Resize(width, height);
}


void QtGlWidget::mousePressEvent(QMouseEvent *event) {
	Rect r;
	
	r.X = event->x();
	r.Y = event->y();
	r.Width = 1;
	r.Height = 1;

	const std::vector<unsigned int> select = m_RenderBackend.Select(r);
	
	if (!select.empty()) {
		std::cout << "Selected object(s): ";
		for (unsigned int i = 0; i < select.size(); i++) {
			std::cout << select[i] << " ";
		}
		std::cout << std::endl;
	}
	
	updateGL();
}


void QtGlWidget::mouseMoveEvent(QMouseEvent *event) {
	std::cout << "Mouse position: (" << event->x() << ", " << event->y() << ")" << std::endl;
}


void QtGlWidget::CalculateFrameRate() {
	struct timeval now;
	double elapsedTime;
	
	gettimeofday(&now, NULL);
	
	elapsedTime = (now.tv_sec - m_LastUpdate.tv_sec) * 1000.0;
    elapsedTime += (now.tv_usec - m_LastUpdate.tv_usec) / 1000.0;
    
    m_LastUpdate = now;
    
    if (elapsedTime != 0.0) m_FrameRate = 1000.0 / elapsedTime;
}

