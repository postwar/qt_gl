#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vector.hpp"
#include "Color.hpp"

class Light {
	public:
		Light();
		virtual ~Light();
		void SetPosition(const Vector3 &position);
		const Vector3 &GetPosition() const;
		void SetAmbientColor(const Color &ambient);
		const Color &GetAmbientColor() const;
		void SetDiffuseColor(const Color &diffuse);
		const Color &GetDiffuseColor() const;
		void SetSpecularColor(const Color &specular);
		const Color &GetSpecularColor() const;
		void Apply();
	
	private:
		Vector3 m_Position;
		Color m_Ambient;
		Color m_Diffuse;
		Color m_Specular;
};

#endif

