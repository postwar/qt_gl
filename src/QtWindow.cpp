#include "QtWindow.hpp"
#include <QtGui/QMessageBox>


QtWindow::QtWindow() {
	connect(&m_Timer, SIGNAL(timeout()), this, SLOT(Update()));
	m_Timer.start(20);
	
	QGLFormat format(QGL::SampleBuffers | QGL::AlphaChannel);
	// format.setVersion(3, 0);
	// format.setProfile(QGLFormat::CompatibilityProfile);
	m_Widget = new QtGlWidget(format);
	
	m_QuitButton = new QPushButton("Quit");
	connect(m_QuitButton, SIGNAL(clicked()), this, SLOT(Quit()));

	m_Layout.addWidget(m_Widget);
	m_Layout.addWidget(m_QuitButton);
	setLayout(&m_Layout);
}


QtWindow::~QtWindow() {
}


void QtWindow::Update() {
	m_Widget->Update();
}


void QtWindow::Quit() {
	QMessageBox::StandardButton choice = QMessageBox::question(this, "Quit?", "Sure you want to quit?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes );
	
	switch( choice ) {
		case QMessageBox::No:
		return;

		case QMessageBox::Yes:
		default:
			close();
	}
}
