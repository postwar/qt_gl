#include "Material.hpp"
#include <GL/glew.h>


Material::Material() {
	m_Ambient.Red = 0.2;
	m_Ambient.Green = 0.2;
	m_Ambient.Blue = 0.2;
	m_Ambient.Alpha = 1.0;
	m_Diffuse.Red = 0.8;
	m_Diffuse.Green = 0.8;
	m_Diffuse.Blue = 0.8;
	m_Diffuse.Alpha = 1.0;
	m_Specular.Red = 0.0;
	m_Specular.Green = 0.0;
	m_Specular.Blue = 0.0;
	m_Specular.Alpha = 0.0;
	m_Emission.Red = 0.0;
	m_Emission.Green = 0.0;
	m_Emission.Blue = 0.0;
	m_Emission.Alpha = 1.0;
	m_Shininess = 0.0;
}


Material::~Material() {
}


void Material::SetAmbientColor(const Color &ambient) {
	m_Ambient = ambient;
}


const Color &Material::GetAmbientColor() const {
	return m_Ambient;
}


void Material::SetDiffuseColor(const Color &diffuse) {
	m_Diffuse = diffuse;
}


const Color &Material::GetDiffuseColor() const {
	return m_Diffuse;
}


void Material::SetSpecularColor(const Color &specular) {
	m_Specular = specular;
}


const Color &Material::GetSpecularColor() const {
	return m_Specular;
}


void Material::SetEmissionColor(const Color &emission) {
	m_Emission = emission;
}


const Color &Material::GetEmissionColor() const {
	return m_Emission;
}


void Material::SetShininess(float shininess) {
	m_Shininess = shininess;
}


float Material::GetShininess() const {
	return m_Shininess;
}


void Material::Bind() const {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &m_Ambient.Red);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &m_Diffuse.Red);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &m_Specular.Red);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_Shininess);

	// see: http://wiki.delphigl.com/index.php/Materialsammlung
	// blending for transparent materials
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

