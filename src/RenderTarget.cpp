#include "RenderTarget.hpp"
#include <iostream>
#include <string>
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
	
	CheckErrors();
}


void RenderTarget::AddTexture(Texture *texture) {
	int nextTexture = m_Textures.size();
	GLuint textureId = texture->m_TextureId;

	glBindTexture(GL_TEXTURE_2D, textureId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + nextTexture, GL_TEXTURE_2D, textureId, 0);
	m_Buffer.push_back(GL_COLOR_ATTACHMENT0 + nextTexture);

	m_Textures.push_back(texture);
	
	std::cout << "Texture added to RenderTarget" << std::endl;
	
	CheckErrors();
}


void RenderTarget::Bind() const {
	glPushAttrib(GL_VIEWPORT_BIT | GL_COLOR_BUFFER_BIT);	
	glViewport(0.0, 0.0, m_Width, m_Height);
	
	glBindFramebuffer(GL_FRAMEBUFFER,  m_Fbo);
	glDrawBuffers(m_Buffer.size(), &m_Buffer[0]);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void RenderTarget::UnBind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glPopAttrib();
}


void RenderTarget::CheckErrors() const {
	std::string msg = "";
	
	switch(glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			msg = "FBO supported and complete";
		break;

		case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
			msg = "Unsupported framebuffer format";
		break;
		
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
			msg = "Framebuffer incomplete, missing attachment";
		break;
		
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
			msg = "Framebuffer incomplete, incomplete attachment";
		break;
		
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			msg = "Framebuffer incomplete, attached images must have same dimensions";
		break;
		
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
			msg = "Framebuffer incomplete, attached images must have same format";
		break;
		
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
			msg = "Framebuffer incomplete, missing draw buffer";
		break;
		
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
			msg = "Framebuffer incomplete, missing read buffer";
		break;
		
		default:
			msg = "Unknown error";
		break;
	}

	if (!msg.empty()) std::cout << msg << std::endl;
}

