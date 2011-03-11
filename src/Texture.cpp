#include "Texture.hpp"
#include <QtGui/QImage>
#include <QtOpenGL/QGLWidget>
#include <iostream>


Texture::Texture() {
	m_TextureId = 0;
}


Texture::~Texture() {
	glDeleteTextures(1, &m_TextureId);
}


void Texture::Create(const std::string &file) {
	QImage image;
	
	if (!image.load(file.c_str())) {
		std::cerr << "Loading image failed: " << file << std::endl;
	}
	
	image = QGLWidget::convertToGLFormat(image);
	
	if (m_TextureId == 0) glGenTextures(1, &m_TextureId);
	
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	/*
	// create texture without mip maps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0,
			GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
	*/
	/*
	// use this setting in a 2D engine for sprites
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image.width(), image.height(), GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Texture::CreateSystemTexture(unsigned int width, unsigned int height) {
	if (m_TextureId == 0) glGenTextures(1, &m_TextureId);
	
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_FLOAT, 0);
}


void Texture::Bind() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}


void Texture::UnBind() {
	glDisable(GL_TEXTURE_2D);
}
