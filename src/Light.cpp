#include "Light.hpp"
#include <GL/glew.h>


Light::Light() {
	m_Position.X = 0.0;
	m_Position.Y = 0.0;
	m_Position.Z = 0.0;
	m_Ambient.Red = 0.0;
	m_Ambient.Green = 0.0;
	m_Ambient.Blue = 0.0;
	m_Ambient.Alpha = 0.0;
	m_Diffuse.Red = 1.0;
	m_Diffuse.Green = 1.0;
	m_Diffuse.Blue = 1.0;
	m_Diffuse.Alpha = 1.0;
	m_Specular.Red = 1.0;
	m_Specular.Green = 1.0;
	m_Specular.Blue = 1.0;
	m_Specular.Alpha = 1.0;
}


Light::~Light() {
}


void Light::SetPosition(const Vector3 &position) {
	m_Position = position;
}

const Vector3 &Light::GetPosition() const {
	return m_Position;
}


void Light::SetAmbientColor(const Color &ambient) {
	m_Ambient = ambient;
}


const Color &Light::GetAmbientColor() const {
	return m_Ambient;
}


void Light::SetDiffuseColor(const Color &diffuse) {
	m_Diffuse = diffuse;
}


const Color &Light::GetDiffuseColor() const {
	return m_Diffuse;
}


void Light::SetSpecularColor(const Color &specular) {
	m_Specular = specular;
}


const Color &Light::GetSpecularColor() const {
	return m_Specular;
}


void Light::Apply() {
	GLfloat position[4];
	
	position[0] = m_Position.X;
	position[1] = m_Position.Y;
	position[2] = m_Position.Z;
	position[3] = 1.0;
	
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, &m_Ambient.Red);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &m_Diffuse.Red);
	glLightfv(GL_LIGHT0, GL_SPECULAR, &m_Specular.Red);
}

