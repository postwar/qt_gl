#include "WorldObject.hpp"

unsigned int WorldObject::nextObjectId = 0;


WorldObject::WorldObject() {
	m_ObjectId = nextObjectId;
	nextObjectId++;
}


WorldObject::~WorldObject() {
	for (unsigned int i = 0; i < m_Textures.size(); i++) {
		delete m_Textures[i];
	}
	
	delete m_Mesh;
	delete m_Shader;
}


void WorldObject::SetTextures(const std::vector<TextureLayer *> &textures) {
	m_Textures = textures;
}


void WorldObject::SetMesh(Mesh *mesh) {
	m_Mesh = mesh;
}


void WorldObject::SetShader(Shader *shader) {
	m_Shader = shader;
}


void WorldObject::Translate(float x, float y, float z) {
	m_Position.X += x;
	m_Position.Y += y;
	m_Position.Z += z;
}


const Vector3 &WorldObject::GetPosition() const {
	return m_Position;
}


unsigned int WorldObject::GetObjectId() const {
	return m_ObjectId;
}

