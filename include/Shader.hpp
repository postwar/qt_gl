#ifndef SHADER_HPP_
#define SHADER_HPP_

/*
#include <QGLShader>
#include <QGLShaderProgram>
#include <string>

class Shader {
	public:
		Shader();
		virtual ~Shader();
		/// @param fileVS File name of the vertex shader.
		/// @param fileFS File name of the fragment shader.
		void Create(const std::string &fileVS, const std::string &fileFS);
		void Bind();
		void UnBind();
		std::string DebugInfo();
	
	private:
		std::string ReadFile(const std::string &file) const;
	
	private:
		QGLShader m_VertexShader;
		QGLShader m_FragmentShader;
		QGLShaderProgram m_ShaderProgram;
		std::string m_VertexShaderFile;
		std::string m_FragmentShaderFile;
};
*/

/*
#include <GL/gl.h>
#include <GL/glext.h>
*/
#include <GL/glew.h>
#include <string>

class Shader {
	public:
		Shader();
		virtual ~Shader();
		/// @param fileVS File name of the vertex shader.
		/// @param fileFS File name of the fragment shader.
		void Create(const std::string &fileVS, const std::string &fileFS);
		void Bind();
		void UnBind();
		std::string DebugInfo();
	
	private:
		std::string ReadFile(const std::string &file) const;
	
	private:
		GLuint m_VertexShader;
		GLuint m_FragmentShader;
		GLuint m_ShaderProgram;
		std::string m_VertexShaderFile;
		std::string m_FragmentShaderFile;
};

#endif
