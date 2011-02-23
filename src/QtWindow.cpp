#include "QtWindow.hpp"


QtWindow::QtWindow() {
	connect(&m_Timer, SIGNAL(timeout()), this, SLOT(Update()));
	m_Timer.start(0);
	
	QGLFormat format(QGL::SampleBuffers | QGL::AlphaChannel);
	format.setVersion(3, 0);
	format.setProfile(QGLFormat::CompatibilityProfile);
	m_Widget = new QtGlWidget(format);
	
	m_Layout.addWidget(m_Widget);
	setLayout(&m_Layout);
}


QtWindow::~QtWindow() {
}


void QtWindow::Update() {
	m_Widget->Update();
}
