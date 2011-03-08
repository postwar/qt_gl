#include "WorldObject.hpp"

unsigned int WorldObject::nextObjectId = 0;


WorldObject::WorldObject() {
	m_ObjectId = nextObjectId;
	nextObjectId++;
}


WorldObject::~WorldObject() {
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


const std::vector<TextureLayer *> &WorldObject::GetTextures() const {
	return m_Textures;
}


const Mesh *WorldObject::GetMesh() const {
	return m_Mesh;
}


const Shader *WorldObject::GetShader() const {
	return m_Shader;
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

