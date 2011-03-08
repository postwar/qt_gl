#include "Mesh.hpp"
#include <iostream>


const int Mesh::POSITION_OFFSET = 0;
const int Mesh::NORMAL_OFFSET = 12;
const int Mesh::TEXTURE_COORD_OFFSET = 24;
const int Mesh::TEXTURE_COORD_SIZE = 8;



#ifndef USE_QT_VBO

Mesh::Mesh() {
}


Mesh::~Mesh() {
	glDeleteBuffers(1, &m_VboId);
	glDeleteBuffers(1, &m_IboId);
}


void Mesh::Create(const VertexData &vertices) {
	if (!vertices.Validate()) {
		std::cout << "Vertex data invalid" << std::endl;
		return;
	}
	
	m_VertexSize = vertices.ElementsPerVertex();
	m_IndexStart = 0;
	m_IndexEnd = vertices.Indices.size();
	m_TextureCoordCount = vertices.TextureCoordinateCount;
	
	float buffer[vertices.ElementsPerVertex()];

	// Vertex Buffer Object
	glGenBuffers(1, &m_VboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), NULL, GL_STATIC_DRAW);
	
	int index = 0;
	for (unsigned int i = 0; i < vertices.VertexCount; i++) {
		// write positions
		buffer[index] = vertices.Position[i].X; index++;
		buffer[index] = vertices.Position[i].Y; index++;
		buffer[index] = vertices.Position[i].Z; index++;
		// write normals
		buffer[index] = vertices.Normal[i].X; index++;
		buffer[index] = vertices.Normal[i].Y; index++;
		buffer[index] = vertices.Normal[i].Z; index++;
		
		// write texture coordinates
		for (unsigned int j = 0; j < vertices.TextureCoordinateCount; j++) {
			buffer[index] = vertices.TextureCoordinates[i][j].X; index++;
			buffer[index] = vertices.TextureCoordinates[i][j].Y; index++;
		}
	}
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buffer), buffer);
	
	
	
	// Index Buffer Object
	glGenBuffers(1, &m_IboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices.Indices), NULL, GL_STATIC_DRAW);
	
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(vertices.Indices), &vertices.Indices[0]);
}


void Mesh::Bind() const {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IboId);
	
	for (unsigned int i = 0; i < m_TextureCoordCount; i++) {
		char *offset = BUFFER_OFFSET(TEXTURE_COORD_OFFSET + i * TEXTURE_COORD_SIZE);
		
		glClientActiveTexture(GL_TEXTURE0 + i);
		glTexCoordPointer(2, GL_FLOAT, m_VertexSize, offset);
	}
	
	glNormalPointer(GL_FLOAT, m_VertexSize, BUFFER_OFFSET(NORMAL_OFFSET));
	// glVertexPointer should be the last array pointer to be set
	glVertexPointer(3, GL_FLOAT, m_VertexSize, BUFFER_OFFSET(POSITION_OFFSET));
}


void Mesh::UnBind() const {
}


void Mesh::Render() const {
	GLuint count = m_IndexEnd - m_IndexStart;
	
	glDrawRangeElements(GL_TRIANGLES, m_IndexStart, m_IndexEnd, count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
}



#else



Mesh::Mesh() : m_Vbo(QGLBuffer::VertexBuffer), m_Ibo(QGLBuffer::IndexBuffer) {
}


Mesh::~Mesh() {
}


void Mesh::Create(const VertexData &vertices) {
	if (!vertices.Validate()) {
		std::cout << "Vertex data invalid" << std::endl;
		return;
	}
	
	m_VertexSize = vertices.ElementsPerVertex();
	m_IndexStart = 0;
	m_IndexEnd = vertices.Indices.size();
	m_TextureCoordCount = vertices.TextureCoordinateCount;
	
	float buffer[vertices.ElementsPerVertex()];

	// Vertex Buffer Object
	m_Vbo.create();
	m_Vbo.bind();
	m_Vbo.setUsagePattern(QGLBuffer::StaticDraw);
	
	int index = 0;
	for (unsigned int i = 0; i < vertices.VertexCount; i++) {
		// write positions
		buffer[index] = vertices.Position[i].X; index++;
		buffer[index] = vertices.Position[i].Y; index++;
		buffer[index] = vertices.Position[i].Z; index++;
		// write normals
		buffer[index] = vertices.Normal[i].X; index++;
		buffer[index] = vertices.Normal[i].Y; index++;
		buffer[index] = vertices.Normal[i].Z; index++;
		
		// write texture coordinates
		for (unsigned int j = 0; j < vertices.TextureCoordinateCount; j++) {
			buffer[index] = vertices.TextureCoordinates[i][j].X; index++;
			buffer[index] = vertices.TextureCoordinates[i][j].Y; index++;
		}
	}
	
	// glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buffer), buffer);
	m_Vbo.allocate(buffer, sizeof(buffer));
	
	
	
	// Index Buffer Object
	m_Ibo.create();
	m_Ibo.bind();
	m_Ibo.setUsagePattern(QGLBuffer::StaticDraw);
	
	m_Ibo.allocate(&vertices.Indices[0], sizeof(vertices.Indices));
}


void Mesh::Bind() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	m_Vbo.bind();
	m_Ibo.bind();
	
	for (unsigned int i = 0; i < m_TextureCoordCount; i++) {
		char *offset = BUFFER_OFFSET(TEXTURE_COORD_OFFSET + i * TEXTURE_COORD_SIZE);
		
		glClientActiveTexture(GL_TEXTURE0 + i);
		glTexCoordPointer(2, GL_FLOAT, m_VertexSize, offset);
	}
	
	glNormalPointer(GL_FLOAT, m_VertexSize, BUFFER_OFFSET(NORMAL_OFFSET));
	// glVertexPointer should be the last array pointer to be set
	glVertexPointer(3, GL_FLOAT, m_VertexSize, BUFFER_OFFSET(POSITION_OFFSET));
}


void Mesh::UnBind() {
}


void Mesh::Render() {
	GLuint count = m_IndexEnd - m_IndexStart;
	
	glDrawRangeElements(GL_TRIANGLES, m_IndexStart, m_IndexEnd, count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
}

#endif

