#include "QtCore.hpp"
#include <iostream>


QtCore::QtCore(int argc, char *argv[])
		: m_Application(argc, argv) {
}


QtCore::~QtCore() {
}


void QtCore::Initialize() {
	// m_Window.setWindowFlags( Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint );
	// m_Window.showFullScreen();
	
	m_Window.show();
}


int QtCore::Run() {
	return m_Application.exec();
}
