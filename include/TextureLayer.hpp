#ifndef TEXTURELAYER_HPP_
#define TEXTURELAYER_HPP_

#include <GL/glew.h>
#include <string>

class TextureLayer {
	public:
		TextureLayer();
		virtual ~TextureLayer();
		void Create(const std::string &file);
		void Bind();
		void UnBind();
	
	private:
		TextureLayer(const TextureLayer &texture);
		TextureLayer &operator =(const TextureLayer &texture);
	
	private:
		GLuint m_TextureId;
};

#endif
