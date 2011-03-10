#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <GL/glew.h>
#include <string>

class Texture {
	public:
		Texture();
		virtual ~Texture();
		void Create(const std::string &file);
		void Bind();
		void UnBind();
	
	private:
		Texture(const Texture &texture);
		Texture &operator =(const Texture &texture);
	
	private:
		GLuint m_TextureId;
};

#endif
