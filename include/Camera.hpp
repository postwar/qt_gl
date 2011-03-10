#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Vector.hpp"

class Camera {
	public:
		Camera();
		Camera(const Camera &camera);
		virtual ~Camera();
		Camera &operator =(const Camera &camera);
		void Resize(int width, int height);
		void Move(float x, float y, float z);
		void Rotate(float x, float y, float z);
		const Vector3 &GetPosition() const;
		const Vector3 &GetRotation() const;
		void Bind() const;
	
	private:
		Vector3 m_Position;
		Vector3 m_Rotation;
		int m_ViewportWidth;
		int m_ViewportHeight;
};

#endif
