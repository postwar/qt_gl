#include "Camera.hpp"
#include <GL/gl.h>


Camera::Camera() {
}


Camera::~Camera() {
}


void Camera::Resize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	glViewport(0, 0, width, height);
	glOrtho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, 0, 512);
	// glFrustum(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, 0, 128);
	// glFrustum(-1.0, 1.0, -1.0, 1.0, 0, 128);
	
	glMatrixMode(GL_MODELVIEW);
}


void Camera::Move(float x, float y, float z) {
	glTranslatef(x, y, z);
}


void Camera::Rotate(float x, float y, float z) {
	glRotatef(x, 1.0, 0.0, 0.0);
	glRotatef(y, 0.0, 1.0, 0.0);
	glRotatef(z, 0.0, 0.0, 1.0);
}

