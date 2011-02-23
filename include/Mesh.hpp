#ifndef MESH_HPP_
#define MESH_HPP_

#include <GL/glew.h>
#include <vector>
#include "VertexData.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class Mesh {
	public:
		Mesh();
		virtual ~Mesh();
		void Create(const VertexData &vertices);
		void Bind();
		void UnBind();
		void Render();
	
	private:
		Mesh(const Mesh &mesh);
		Mesh &operator =(const Mesh &mesh);
	
	private:
		GLuint m_VboId;
		GLuint m_IboId;
		GLuint m_IndexStart;
		GLuint m_IndexEnd;
		unsigned int m_VertexSize;
		unsigned int m_TextureCoordCount;
		static const int POSITION_OFFSET;
		static const int NORMAL_OFFSET;
		static const int TEXTURE_COORD_OFFSET;
		static const int TEXTURE_COORD_SIZE;
};





/*
#include <QGLBuffer>
#include <vector>
#include "VertexData.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class Mesh {
	public:
		Mesh();
		virtual ~Mesh();
		void Create(const VertexData &vertices);
		void Bind();
		void UnBind();
		void Render();
	
	private:
		Mesh(const Mesh &mesh);
		Mesh &operator =(const Mesh &mesh);
	
	private:
		QGLBuffer m_Vbo;
		QGLBuffer m_Ibo;
		GLuint m_IndexStart;
		GLuint m_IndexEnd;
		unsigned int m_VertexSize;
		unsigned int m_TextureCoordCount;
		static const int POSITION_OFFSET;
		static const int NORMAL_OFFSET;
		static const int TEXTURE_COORD_OFFSET;
		static const int TEXTURE_COORD_SIZE;
};
*/

#endif
