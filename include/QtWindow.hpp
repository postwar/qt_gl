#ifndef QTWINDOW_HPP_
#define QTWINDOW_HPP_

#include <QtGui/QWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtCore/QTimer>
#include "QtGlWidget.hpp"

class QtWindow : public QWidget {
	Q_OBJECT
	
	public:
		QtWindow();
		virtual ~QtWindow();
	
	private slots:
		void Update();
		void Quit();
	
	private:
		QtGlWidget *m_Widget;
		QGridLayout m_Layout;
		QTimer m_Timer;
		QPushButton *m_QuitButton;
};

#endif
