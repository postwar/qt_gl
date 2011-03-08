#ifndef WORLDOBJECT_HPP_
#define WORLDOBJECT_HPP_

#include "Mesh.hpp"
#include "Shader.hpp"
#include "TextureLayer.hpp"
#include "Vector.hpp"

class WorldObject {
	public:
		WorldObject();
		virtual ~WorldObject();
		void SetTextures(const std::vector<TextureLayer *> &textures);
		void SetMesh(Mesh *mesh);
		void SetShader(Shader *shader);
		void Translate(float x, float y, float z);
		const Vector3 &GetPosition() const;
		unsigned int GetObjectId() const;
	
	private:
		static unsigned int nextObjectId;
		
		std::vector<TextureLayer *> m_Textures;
		Mesh *m_Mesh;
		Shader *m_Shader;
		Vector3 m_Position;
		unsigned int m_ObjectId;
};

#endif
