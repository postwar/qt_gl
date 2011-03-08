#ifndef QTGLWIDGET_HPP_
#define QTGLWIDGET_HPP_

#include <vector>
#include "RenderBackend.hpp"
#include "Scene.hpp"
#include <QtOpenGL/QGLWidget>
#include <sys/time.h>

class QtGlWidget : public QGLWidget {
	Q_OBJECT
	
	public:
		QtGlWidget(QGLFormat format, QWidget *parent = 0);
		virtual ~QtGlWidget();
		void Update();
		QSize minimumSizeHint() const;
		QSize sizeHint() const;

	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height);
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
	
	private:
		void CalculateFrameRate();
	
	private:
		RenderBackend m_RenderBackend;
		Scene m_Scene;
		struct timeval m_LastUpdate;
		double m_FrameRate;
};

#endif
