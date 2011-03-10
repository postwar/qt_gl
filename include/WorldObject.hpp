#ifndef WORLDOBJECT_HPP_
#define WORLDOBJECT_HPP_

#include "Vector.hpp"
#include <vector>

class Material;
class Mesh;
class Shader;
class TextureLayer;

class WorldObject {
	public:
		WorldObject();
		virtual ~WorldObject();
		void SetTextures(const std::vector<TextureLayer *> &textures);
		void SetMesh(Mesh *mesh);
		void SetShader(Shader *shader);
		void SetMaterial(Material *material);
		const std::vector<TextureLayer *> &GetTextures() const;
		const Mesh *GetMesh() const;
		const Shader *GetShader() const;
		const Material *GetMaterial() const;
		void Move(float x, float y, float z);
		void Rotate(float x, float y, float z);
		const Vector3 &GetPosition() const;
		const Vector3 &GetRotation() const;
		unsigned int GetObjectId() const;
	
	private:
		static unsigned int nextObjectId;
		
		std::vector<TextureLayer *> m_Textures;
		Mesh *m_Mesh;
		Shader *m_Shader;
		Material *m_Material;
		Vector3 m_Position;
		Vector3 m_Rotation;
		unsigned int m_ObjectId;
};

#endif
