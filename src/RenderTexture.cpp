#include "RenderTexture.hpp"


RenderTexture::RenderTexture() {
	m_TextureId = 0;
}


RenderTexture::~RenderTexture() {
	glDeleteTextures(1, &m_TextureId);
}


void RenderTexture::Create(Format format, unsigned int width, unsigned int height) {
	if (m_TextureId == 0) glGenTextures(1, &m_TextureId);
	
	GLint internalFormat = ConvertInternalFormat(format);
	GLint externalFormat = ConvertExternalFormat(format);
	GLint type = ConvertType(format);
	
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
/*
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_NONE);
*/
	
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, externalFormat, type, NULL);
	// glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, externalFormat, GL_FLOAT, NULL);
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


GLint RenderTexture::ConvertInternalFormat(Format format) const {
	switch (format) {
		case R8_G8_B8_A8: return GL_RGBA;
		case R10_G10_B10_A2: return GL_RGB10_A2;
		case R11F_G11F_B10F: return GL_R11F_G11F_B10F;
		case DEPTH16: return GL_DEPTH_COMPONENT16;
		case DEPTH24: return GL_DEPTH_COMPONENT24;
		case DEPTH32F: return GL_DEPTH_COMPONENT32F;
		case DEPTH24_STENCIL8: return GL_DEPTH24_STENCIL8;
		case DEPTH32F_STENCIL8: return GL_DEPTH32F_STENCIL8;
	};
}


GLint RenderTexture::ConvertExternalFormat(Format format) const {
	switch (format) {
		case R8_G8_B8_A8:
		case R10_G10_B10_A2:
		case R11F_G11F_B10F:
			return GL_RGBA;
		
		case DEPTH16:
		case DEPTH24:
		case DEPTH32F:
		case DEPTH24_STENCIL8:
		case DEPTH32F_STENCIL8:
			return GL_DEPTH_COMPONENT;
	};
}


GLint RenderTexture::ConvertType(Format format) const {
	switch (format) {
		case R8_G8_B8_A8:
		case R10_G10_B10_A2:
		case DEPTH16:
		case DEPTH24:
		case DEPTH24_STENCIL8:
			return GL_UNSIGNED_BYTE;
		
		case DEPTH32F:
		case R11F_G11F_B10F:
		case DEPTH32F_STENCIL8:
			return GL_FLOAT;
	};
}

