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
	m_Diffuse.Red = 0.0;
	m_Diffuse.Green = 0.0;
	m_Diffuse.Blue = 0.0;
	m_Diffuse.Alpha = 0.0;
	m_Specular.Red = 0.0;
	m_Specular.Green = 0.0;
	m_Specular.Blue = 0.0;
	m_Specular.Alpha = 0.0;
	m_Shininess = 0.0;
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


void Light::SetShininess(float shininess) {
	m_Shininess = shininess;
}


float Light::GetShininess() const {
	return m_Shininess;
}


void Light::Apply() {
	// see: http://wiki.delphigl.com/index.php/Materialsammlung
	// blending for transparent materials
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
