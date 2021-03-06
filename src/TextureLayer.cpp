#include "TextureLayer.hpp"
#include <QtGui/QImage>
#include <QtOpenGL/QGLWidget>


TextureLayer::TextureLayer() {
}


TextureLayer::~TextureLayer() {
	glDeleteTextures(1, &m_TextureId);
}


void TextureLayer::Create(const std::string &file) {
	QImage image;
	
	image.load(file.c_str());
	image = QGLWidget::convertToGLFormat(image);
	
	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0,
			GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void TextureLayer::Bind() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}


void TextureLayer::UnBind() {
	glDisable(GL_TEXTURE_2D);
}
