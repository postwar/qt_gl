#include "Shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>


#ifndef USE_QT_SHADERS

Shader::Shader() {
}


Shader::~Shader() {
}


void Shader::Create(const std::string &fileVS, const std::string &fileFS) {
	m_VertexShaderFile = fileVS;
	m_FragmentShaderFile = fileFS;

	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vs = ReadFile(fileVS);
	std::string fs = ReadFile(fileFS);
	
	const char *pvs = vs.c_str();
	const char *pfs = fs.c_str();

	glShaderSource(m_VertexShader, 1, &pvs, NULL);
	glShaderSource(m_FragmentShader, 1, &pfs, NULL);

	glCompileShader(m_VertexShader);
	glCompileShader(m_FragmentShader);
	
	m_VertexShaderInfoLog = GetShaderInfoLog(m_VertexShader);
	m_FragmentShaderInfoLog = GetShaderInfoLog(m_FragmentShader);

	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, m_VertexShader);
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	
	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);

	glLinkProgram(m_ShaderProgram);

	m_ProgramInfoLog = GetProgramInfoLog(m_ShaderProgram);	
}


void Shader::Bind() {
	glUseProgram(m_ShaderProgram);
	
	GLint samplerLocation;
	
	samplerLocation = glGetUniformLocation(m_ShaderProgram, "Tex0");
	if (samplerLocation != -1) {
		glUniform1i(samplerLocation, 0);
	} else {
		// std::cerr << "Error: Find location 'Tex0'" << std::endl;
	}
	
	samplerLocation = glGetUniformLocation(m_ShaderProgram, "Tex1");
	if (samplerLocation != -1) {
		glUniform1i(samplerLocation, 1);
	} else {
		// std::cerr << "Error: Find location 'Tex1'" << std::endl;
	}
	
	samplerLocation = glGetUniformLocation(m_ShaderProgram, "Tex2");
	if (samplerLocation != -1) {
		glUniform1i(samplerLocation, 2);
	} else {
		// std::cerr << "Error: Find location 'Tex2'" << std::endl;
	}
}


void Shader::UnBind() {
	glUseProgram(0);
}


std::string Shader::DebugInfo() {
	std::stringstream info;

	info << "Vertex shader: " << m_VertexShaderFile << std::endl;
	info << "Fragment shader: " << m_FragmentShaderFile << std::endl;
	
	if (!m_VertexShaderInfoLog.empty()) {
		info << "Vertex shader info: ";
		info << m_VertexShaderInfoLog << std::endl;
	}
	
	if (!m_FragmentShaderInfoLog.empty()) {
		info << "Fragment shader info: ";
		info << m_FragmentShaderInfoLog << std::endl;
	}
	
	if (!m_ProgramInfoLog.empty()) {
		info << "Program info: ";
		info << m_ProgramInfoLog << std::endl;
	}
	
	// the shader program must be bound to query the information
	glUseProgram(m_ShaderProgram);

	GLint activeUniforms;
	glGetProgramiv(m_ShaderProgram, GL_ACTIVE_UNIFORMS, &activeUniforms);
	info << "Active uniforms: " << activeUniforms << std::endl;
	
	GLint activeUniformMaxLength;
	glGetProgramiv(m_ShaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &activeUniformMaxLength);
	
	for (int i = 0; i < activeUniforms; i++) {
		GLsizei bufSize = activeUniformMaxLength;
		GLsizei length;
		GLuint index = i;
		GLint size;
		GLenum type;
		char name[bufSize];
		memset(name, bufSize, 0);
	
		glGetActiveUniform(m_ShaderProgram, index, bufSize, &length, &size, &type, name);
		info << "Uniform " << i << ": " << name << std::endl;
	}
	
	return info.str();
}


std::string Shader::ReadFile(const std::string &file) const {
	std::ifstream fstr(file.c_str());
	std::stringstream sstr;
	std::string line;
	
	while (getline(fstr, line, '\n')) {
		sstr << line << std::endl;
	}

	return sstr.str();
}


std::string Shader::GetShaderInfoLog(GLuint obj) const {
	std::stringstream sstr;
	int infologLength = 0;
	int charsWritten = 0;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 1) {
		char infoLog[infologLength];
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		
		sstr << "Error: " << infoLog;
	}
	
	return sstr.str();
}


std::string Shader::GetProgramInfoLog(GLuint obj) const {
	std::stringstream sstr;
	int infologLength = 0;
	int charsWritten  = 0;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 1) {
		char infoLog[infologLength];
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		
		sstr << "Error: " << infoLog;
	}
	
	return sstr.str();
}



#else



Shader::Shader() : m_VertexShader(QGLShader::Vertex), m_FragmentShader(QGLShader::Fragment), m_ShaderProgram() {
}


Shader::~Shader() {
}


void Shader::Create(const std::string &fileVS, const std::string &fileFS) {
	m_VertexShaderFile = fileVS;
	m_FragmentShaderFile = fileFS;
	
	if (!m_VertexShader.compileSourceFile(fileVS.c_str())) {
		std::cout << "Vertex shader error: " << m_VertexShader.log().toStdString() << std::endl;
	}
	if (!m_FragmentShader.compileSourceFile(fileFS.c_str())) {
		std::cout << "Fragment shader error: " << m_FragmentShader.log().toStdString() << std::endl;
	}
	
	
	if (!m_ShaderProgram.addShader(&m_VertexShader)) {
		std::cout << "Adding vertex shader failed: " << m_ShaderProgram.log().toStdString() << std::endl;
	}
	if (!m_ShaderProgram.addShader(&m_FragmentShader)) {
		std::cout << "Adding fragment shader failed: " << m_ShaderProgram.log().toStdString() << std::endl;
	}
	
	
	if (!m_ShaderProgram.link()) {
		std::cout << "Link error: " << m_ShaderProgram.log().toStdString() << std::endl;
	}
}


void Shader::Bind() {
	m_ShaderProgram.bind();
	
	int samplerLocation;
	
	samplerLocation = m_ShaderProgram.uniformLocation("Tex0");
	if (samplerLocation != -1) {
		m_ShaderProgram.setUniformValue(samplerLocation, 0);
	} else {
		// std::cerr << "Error: Find location 'Tex0'" << std::endl;
	}
	
	samplerLocation = m_ShaderProgram.uniformLocation("Tex1");
	if (samplerLocation != -1) {
		m_ShaderProgram.setUniformValue(samplerLocation, 1);
	} else {
		// std::cerr << "Error: Find location 'Tex1'" << std::endl;
	}
}


void Shader::UnBind() {
}


std::string Shader::DebugInfo() {
	std::stringstream info;

	info << "Vertex shader: " << m_VertexShaderFile << std::endl;
	info << "Fragment shader: " << m_FragmentShaderFile << std::endl;
	
	// the shader program must be bound to query the information
	m_ShaderProgram.bind();
	
	return info.str();
}

#endif

