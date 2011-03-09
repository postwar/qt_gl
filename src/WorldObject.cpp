#include "WorldObject.hpp"

unsigned int WorldObject::nextObjectId = 0;


WorldObject::WorldObject() {
	m_ObjectId = nextObjectId;
	nextObjectId++;
	
	m_Position.X = 0.0;
	m_Position.Y = 0.0;
	m_Position.Z = 0.0;
	m_Rotation.X = 0.0;
	m_Rotation.Y = 0.0;
	m_Rotation.Z = 0.0;
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


void WorldObject::Move(float x, float y, float z) {
	m_Position.X += x;
	m_Position.Y += y;
	m_Position.Z += z;
}


void WorldObject::Rotate(float x, float y, float z) {
	m_Rotation.X += x;
	m_Rotation.Y += y;
	m_Rotation.Z += z;
}


const Vector3 &WorldObject::GetPosition() const {
	return m_Position;
}


const Vector3 &WorldObject::GetRotation() const {
	return m_Rotation;
}


unsigned int WorldObject::GetObjectId() const {
	return m_ObjectId;
}

