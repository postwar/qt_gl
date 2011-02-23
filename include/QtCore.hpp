#ifndef QTCORE_HPP_
#define QTCORE_HPP_

#include <QtGui/QApplication>
#include "QtWindow.hpp"

class QtCore {
	public:
		QtCore(int argc, char *argv[]);
		virtual ~QtCore();
		void Initialize();
		int Run();
	
	private:
		QApplication m_Application;
		QtWindow m_Window;
};

#endif
