#include "RenderTexture.hpp"


RenderTexture::RenderTexture() {
	m_TextureId = 0;
}


RenderTexture::~RenderTexture() {
	glDeleteTextures(1, &m_TextureId);
}


void RenderTexture::Create(unsigned int width, unsigned int height) {
	if (m_TextureId == 0) glGenTextures(1, &m_TextureId);
	
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
}


void RenderTexture::Bind() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}


void RenderTexture::UnBind() {
	glDisable(GL_TEXTURE_2D);
}
