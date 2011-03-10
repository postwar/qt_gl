#include "Camera.hpp"
#include <GL/glew.h>


Camera::Camera() {
	m_Position.X = 0.0;
	m_Position.Y = 0.0;
	m_Position.Z = 0.0;
	m_Rotation.X = 0.0;
	m_Rotation.Y = 0.0;
	m_Rotation.Z = 0.0;
}


Camera::Camera(const Camera &camera) {
	m_Position.X = camera.m_Position.X;
	m_Position.Y = camera.m_Position.Y;
	m_Position.Z = camera.m_Position.Z;
	m_Rotation.X = camera.m_Rotation.X;
	m_Rotation.Y = camera.m_Rotation.Y;
	m_Rotation.Z = camera.m_Rotation.Z;
	m_ViewportWidth = camera.m_ViewportWidth;
	m_ViewportHeight = camera.m_ViewportHeight;
}


Camera::~Camera() {
}


Camera &Camera::operator =(const Camera &camera) {
	if (&camera != this) {
		m_Position.X = camera.m_Position.X;
		m_Position.Y = camera.m_Position.Y;
		m_Position.Z = camera.m_Position.Z;
		m_Rotation.X = camera.m_Rotation.X;
		m_Rotation.Y = camera.m_Rotation.Y;
		m_Rotation.Z = camera.m_Rotation.Z;
		m_ViewportWidth = camera.m_ViewportWidth;
		m_ViewportHeight = camera.m_ViewportHeight;
	}
	
	return *this;
}


void Camera::Resize(int width, int height) {
	m_ViewportWidth = width;
	m_ViewportHeight = height;
}


void Camera::Move(float x, float y, float z) {
	m_Position.X += x;
	m_Position.Y += y;
	m_Position.Z += z;
}


void Camera::Rotate(float x, float y, float z) {
	m_Rotation.X += x;
	m_Rotation.Y += y;
	m_Rotation.Z += z;
}


const Vector3 &Camera::GetPosition() const {
	return m_Position;
}


const Vector3 &Camera::GetRotation() const {
	return m_Rotation;
}


void Camera::Bind() const {
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	glViewport(0, 0, m_ViewportWidth, m_ViewportHeight);
	
	// orthogonal projection
	// glOrtho(-m_ViewportWidth / 2.0, m_ViewportWidth / 2.0, -m_ViewportHeight / 2.0, m_ViewportHeight / 2.0, 0.0, 512.0);
	
	// perspective projection
	float aspect = (1.0 * m_ViewportWidth) / (1.0 * m_ViewportHeight);
	gluPerspective(60.0, aspect, 1.0, 512.0);

	
	glMatrixMode(GL_MODELVIEW);

	glTranslatef(-m_Position.X, -m_Position.Y, -m_Position.Z);
	
	glRotatef(m_Rotation.X, 1.0, 0.0, 0.0);
	glRotatef(m_Rotation.Y, 0.0, 1.0, 0.0);
	glRotatef(m_Rotation.Z, 0.0, 0.0, 1.0);
}

