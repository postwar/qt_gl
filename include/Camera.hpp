#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Vector.hpp"

class Camera {
	public:
		Camera();
		virtual ~Camera();
		void Resize(int width, int height);
		void Move(float x, float y, float z);
		void Rotate(float x, float y, float z);
		const Vector3 &GetPosition() const;
		const Vector3 &GetRotation() const;
		void Apply() const;
	
	private:
		Camera(const Camera &camera);
		Camera &operator =(const Camera &camera);
	
	private:
		Vector3 m_Position;
		Vector3 m_Rotation;
		int m_ViewportWidth;
		int m_ViewportHeight;
};

#endif
