#include "RenderTarget.hpp"
#include "Texture.hpp"


RenderTarget::RenderTarget() {
}


RenderTarget::~RenderTarget() {
	glDeleteRenderbuffers(1, &m_DepthBuffer);
	glDeleteFramebuffers(1, &m_Fbo);
}


void RenderTarget::Create(unsigned int width, unsigned int height) {
	m_Width = width;
	m_Height = height;

	// create FBP
	glGenFramebuffers(1, &m_Fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);

	// create depth buffer
	glGenRenderbuffers(1, &m_DepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	
	// attach depth buffer to FBO
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);
}


void RenderTarget::AddTexture(Texture *texture) {
	int nextTexture = m_Textures.size();
	GLuint textureId = texture->m_TextureId;

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + nextTexture, GL_TEXTURE_2D, textureId, 0);
	m_Buffer.push_back(GL_COLOR_ATTACHMENT0 + nextTexture);

	m_Textures.push_back(texture);
}


void RenderTarget::Bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER,  m_Fbo);
	glDrawBuffers(m_Buffer.size(), &m_Buffer[0]);
}


void RenderTarget::UnBind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

