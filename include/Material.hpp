#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "Color.hpp"

class Material {
	public:
		Material();
		virtual ~Material();
		void SetAmbientColor(const Color &ambient);
		const Color &GetAmbientColor() const;
		void SetDiffuseColor(const Color &diffuse);
		const Color &GetDiffuseColor() const;
		void SetSpecularColor(const Color &specular);
		const Color &GetSpecularColor() const;
		void SetEmissionColor(const Color &emission);
		const Color &GetEmissionColor() const;
		void SetShininess(float shininess);
		float GetShininess() const;
		void Apply();
	
	private:
		Color m_Ambient;
		Color m_Diffuse;
		Color m_Specular;
		Color m_Emission;
		float m_Shininess;
};

#endif

