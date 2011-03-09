#include "RenderBackend.hpp"
#include <iostream>
#include "Mesh.hpp"
#include "TextureLayer.hpp"


const int RenderBackend::BUFFER_SIZE = 16;


RenderBackend::RenderBackend() {
	m_SelectionBuffer.resize(4 * BUFFER_SIZE);
}


RenderBackend::~RenderBackend() {
}


void RenderBackend::Initialize() {
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);
	// glClearColor(1.0, 0.0, 1.0, 1.0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	
	m_Shader.Create("../data/shader/selection.vs", "../data/shader/selection.fs");
}


void RenderBackend::StartFrame() {
	m_RenderData.clear();
	ClearScreen();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void RenderBackend::PushRenderData(const WorldObject &data) {
	m_RenderData.push_back(data);
}


void RenderBackend::Render() {
	for (unsigned int i = 0; i < m_RenderData.size(); i++) {
		const Vector3 pos = m_RenderData[i].GetPosition();
		const Vector3 rot = m_RenderData[i].GetRotation();
		glPushMatrix();
		glTranslatef(pos.X, pos.Y, pos.Z);
		glRotatef(rot.X, 1.0, 0.0, 0.0);
		glRotatef(rot.Y, 0.0, 1.0, 0.0);
		glRotatef(rot.Z, 0.0, 0.0, 1.0);
		
		for (unsigned int texture = 0; texture < m_RenderData[i].GetTextures().size(); texture++) {
			glActiveTexture(GL_TEXTURE0 + texture);
			m_RenderData[i].GetTextures()[texture]->Bind();
		}
		m_RenderData[i].GetShader()->Bind();
		m_RenderData[i].GetMesh()->Bind();
		m_RenderData[i].GetMesh()->Render();
		
		glPopMatrix();
	}
}


void RenderBackend::RenderSelect() {
	m_Shader.Bind();

	for (unsigned int i = 0; i < m_RenderData.size(); i++) {
		for (unsigned int texture = 0; texture < m_RenderData[i].GetTextures().size(); texture++) {
			glActiveTexture(GL_TEXTURE0 + texture);
			m_RenderData[i].GetTextures()[texture]->Bind();
		}
		
		// The shader writes the color values in the framebuffer if the object
		// at this position can be selected. Furthermore, it will set the alpha
		// value to 255. If there is no selectable object, the alpha value will
		// be cleared to 0 and not changed by the shader.
		unsigned char r = (i >>  0) & 0xFF;
		unsigned char g = (i >>  8) & 0xFF;
		unsigned char b = (i >> 16) & 0xFF;
		
		glColor3ub(r, g, b);
		
		m_RenderData[i].GetMesh()->Bind();
		m_RenderData[i].GetMesh()->Render();
	}
	glColor4ub(255, 255, 255, 255);
	
	m_Shader.UnBind();
}


const std::vector<unsigned int> &RenderBackend::Select(const Rect &area) {
	GLint viewport[4];
	int width;
	int height;
	float x_off;
	float y_off;
	float x;
	float y;
	
	ClearScreen();
	glGetIntegerv(GL_VIEWPORT, viewport);
	width = viewport[2];
	height = viewport[3];
	// x_off = 1.0 / width;
	// y_off = 1.0 / height;
	x_off = area.Width;
	y_off = area.Height;
	x = area.X - (width / 2);
	y = (height - area.Y) - (height / 2);
	
	m_Selection.clear();

/*
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(x - x_off, x + x_off, y - y_off, y + y_off, 0, 128);
	glMatrixMode(GL_MODELVIEW);
*/
	
	RenderSelect();

/*	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
*/
	
	unsigned char *pixels = new unsigned char[4 * width * height];
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	
	
/*	
	int index = 4 * ((height - area.Y) * width + area.X);
	unsigned int r = pixels[index + 0];
	unsigned int g = pixels[index + 1];
	unsigned int b = pixels[index + 2];
	unsigned int a = pixels[index + 3];
	
	unsigned int id = (r << 0) + (g << 8) + (b << 16);
	std::cout << r << ", " << g << ", " << b << ", " << a << " -> " << id << std::endl;
*/
	
	bool buf[m_RenderData.size()];
	for (unsigned int i = 0; i < m_RenderData.size(); i++) {
		buf[i] = false;
	}
	
	for (int i = area.X; i < area.X + area.Width; i++) {
		for (int j = area.Y; j < area.Y + area.Height; j++) {
			int index = 4 * ((height - j - 1) * width + i);
			unsigned int a = pixels[index + 3];
			
			// If there is an object at the current position, the shader has set
			// the alpha value to 255. Else the alpha value is cleared to 0.
			// If there is an object we calculate it's index and set the
			// according entry in the selection buffer.
			if (a == 255) {
				unsigned int r = pixels[index + 0];
				unsigned int g = pixels[index + 1];
				unsigned int b = pixels[index + 2];
			
				unsigned int id = (r << 0) + (g << 8) + (b << 16);
				buf[id] = true;
			}
		}
	}
	
	for (unsigned int i = 0; i < m_RenderData.size(); i++) {
		if (buf[i]) {
			m_Selection.push_back(m_RenderData[i].GetObjectId());
		}
	}
	
	delete[] pixels;
	
	ClearScreen();
	return m_Selection;
}


void RenderBackend::EndFrame() {
}


void RenderBackend::ClearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

