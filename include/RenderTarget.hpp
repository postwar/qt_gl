#ifndef RENDERTARGET_HPP_
#define RENDERTARGET_HPP_

#include <GL/glew.h>
#include <vector>

class Texture;

/*
 * http://wiki.delphigl.com/index.php/Tutorial_Framebufferobject
 * http://www.opengl.org/wiki/Framebuffer_Object
 * http://www.gamedev.net/page/resources/_//feature/fprogramming/opengl-frame-buffer-object-101-r2331
 * http://www.gamedev.net/page/resources/_/reference/programming/opengl/opengl-frame-buffer-object-201-r2333
 * http://www.songho.ca/opengl/gl_fbo.html
 *
 * Depth texture:
 * glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, texWidth, texHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
 * glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);
 *
 * Image formats:
 * http://www.opengl.org/wiki/Image_Formats
 */
class RenderTarget {
	public:
		RenderTarget();
		virtual ~RenderTarget();
		void Create(unsigned int width, unsigned int height);
		void AddTexture(Texture *texture);
		void Bind() const;
		void UnBind() const;
	
	private:
		void CheckErrors() const;
	
	private:
		unsigned int m_Width;
		unsigned int m_Height;
		std::vector<Texture *> m_Textures;
		std::vector<GLenum> m_Buffer;
		GLuint m_Fbo;
		GLuint m_DepthBuffer;
		GLint m_MaximumAttachments;
		GLint m_MaximumDrawBuffers;
};

#endif

