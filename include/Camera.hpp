#ifndef CAMERA_HPP_
#define CAMERA_HPP_

class Camera {
	public:
		Camera();
		virtual ~Camera();
		void Resize(int width, int height);
		void Move(float x, float y, float z);
		void Rotate(float x, float y, float z);
	
	private:
		Camera(const Camera &camera);
		Camera &operator =(const Camera &camera);
	
	private:
		float m_PositionX;
		float m_PositionY;
		float m_PositionZ;
		float m_RotationX;
		float m_RotationY;
		float m_RotationZ;
};

#endif
