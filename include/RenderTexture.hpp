#ifndef RENDERTEXTURE_HPP_
#define RENDERTEXTURE_HPP_

#include <GL/glew.h>
#include <string>

class RenderTexture {
	/*
	 * RenderTarget needs access to the OpenGL texture name to attach the
	 * texture to a frame buffer object
	 */
	friend class RenderTarget;
	
	public:
		/*
		 * Image formats:
		 * http://www.opengl.org/wiki/Image_Formats
		 */
		enum Format {
			R8_G8_B8_A8,
			R10_G10_B10_A2,
			R11F_G11F_B10F,
			DEPTH_16,
			DEPTH_24,
			DEPTH_32F,
			DEPTH24_STENCIL8,
			DEPTH32F_STENCIL8
		};

	public:
		RenderTexture();
		virtual ~RenderTexture();
		void Create(Format format, unsigned int width, unsigned int height);
		void Bind();
		void UnBind();
	
	private:
		RenderTexture(const RenderTexture &texture);
		RenderTexture &operator =(const RenderTexture &texture);
		GLint ConvertInternalFormat(Format format) const;
		GLint ConvertExternalFormat(Format format) const;
	
	private:
		GLuint m_TextureId;
};

#endif
