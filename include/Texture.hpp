#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <GL/glew.h>
#include <string>

class Texture {
	// RenderTarget needs access to the OpenGL texture name to attach the
	// texture to a frame buffer object
	friend class RenderTarget;

	public:
		Texture();
		virtual ~Texture();
		void Create(const std::string &file);
		void CreateSystemTexture(unsigned int width, unsigned int height);
		void Bind();
		void UnBind();
	
	private:
		Texture(const Texture &texture);
		Texture &operator =(const Texture &texture);
	
	private:
		GLuint m_TextureId;
};

#endif
