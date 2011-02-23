#ifndef QTGLWIDGET_HPP_
#define QTGLWIDGET_HPP_

#include <vector>
#include "RenderBackend.hpp"
#include "Mesh.hpp"
#include "TextureLayer.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include <QtOpenGL/QGLWidget>

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
		RenderBackend m_RenderBackend;
		Camera m_Camera;
		std::vector<RenderData> m_Data;
		std::vector<TextureLayer *> m_Textures;
		Mesh *m_Mesh;
		Shader *m_Shader;
};

#endif
