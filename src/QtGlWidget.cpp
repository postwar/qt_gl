#include "QtGlWidget.hpp"
#include <iostream>
#include <QtGui/QMouseEvent>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>
#include "Objects.hpp"


QtGlWidget::QtGlWidget(QGLFormat format, QWidget *parent)
		// We need the alpha channel for the color picking
		: QGLWidget(format, parent) {
	// showFullScreen();
}


QtGlWidget::~QtGlWidget() {
	for (unsigned int i = 0; i < m_Textures.size(); i++) {
		delete m_Textures[i];
	}
	
	delete m_Mesh;
	delete m_Shader;
}


void QtGlWidget::Update() {
	m_RenderBackend.StartFrame();
	
	for (unsigned int i = 0; i < m_Data.size(); i++) {
		m_RenderBackend.PushRenderData(m_Data[i]);
	}
	
	updateGL();
	m_RenderBackend.EndFrame();
}


QSize QtGlWidget::minimumSizeHint() const {
	return QSize(50, 50);
}


QSize QtGlWidget::sizeHint() const {
	return QSize(800, 600);
}


void QtGlWidget::initializeGL() {
	glewInit();

	TextureLayer *texture1 = new TextureLayer();
	TextureLayer *texture2 = new TextureLayer();
	TextureLayer *texture3 = new TextureLayer();
	m_Mesh = new Mesh();
	m_Mesh->Create(Objects::CreateSquare());
	
	// texture1->Create("../data/gfx/2008_BlastDoor_TextureDiff_large.jpg");
	texture1->Create("../data/gfx/stone_wall.bmp");
	m_Textures.push_back(texture1);
	// texture2->Create("../data/gfx/2008_BlastDoor_TextureNormal_large.jpg");
	texture2->Create("../data/gfx/stone_wall_normal_map.bmp");
	m_Textures.push_back(texture2);
	// texture3->Create("../data/gfx/2008_BlastDoor_TextureSpec_large.jpg");
	texture3->Create("../data/gfx/specular_map.jpg");
	m_Textures.push_back(texture3);


	m_Shader = new Shader();
	m_Shader->Create("../data/shader/test.vs", "../data/shader/test.fs");
	std::cout << m_Shader->DebugInfo() << std::endl;
	
	for (unsigned int i = 0; i < 10; i++) {
		RenderData object;
		object.ObjectId = i;
		object.Texture = m_Textures;
		object.MeshId = m_Mesh;
		object.ShaderId = m_Shader;
		
		m_Data.push_back(object);
	}
	
	m_RenderBackend.Initialize();
}


void QtGlWidget::paintGL() {
	struct timeval t1;
	struct timeval t2;
	double elapsedTime;
	
	
	
	
	static float counter = 0.0;
	counter += 0.01;
		
	float x = cos(counter) * 5;
	float z = sin(counter) * 5;
		
	std::cout << "Light Pos: (" << x << ", " << z << ")" << std::endl;
	
	glEnable(GL_LIGHT0);
	GLfloat position[] = { x, x, z, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
	
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	
	
	gettimeofday(&t1, NULL);
	// m_RenderBackend.RenderSelect();
	m_RenderBackend.Render();
	gettimeofday(&t2, NULL);
	
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
	
	// if (elapsedTime != 0) std::cout << 1.0 / elapsedTime << std::endl;
}


void QtGlWidget::resizeGL(int width, int height) {
	m_Camera.Resize(width, height);
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


void QtGlWidget::mouseMoveEvent(QMouseEvent * /* event */) {
}

