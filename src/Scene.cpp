#include "Scene.hpp"
#include <iostream>
#include <cmath>
#include "Objects.hpp"


Scene::Scene() {
}


Scene::~Scene() {
	for (unsigned int i = 0; i < m_Textures.size(); i++) {
		delete m_Textures[i];
	}
	
	delete m_Mesh;
	delete m_Shader;
}


void Scene::Initialize() {
	TextureLayer *texture1 = new TextureLayer();
	TextureLayer *texture2 = new TextureLayer();
	TextureLayer *texture3 = new TextureLayer();
	m_Mesh = new Mesh();
	m_Mesh->Create(Objects::CreateSquare());
	
	// texture1->Create("../data/gfx/2008_BlastDoor_TextureDiff_large.jpg");
	texture1->Create("../data/gfx/stone_wall.bmp");
	m_Textures.push_back(texture1);
	// texture2->Create("../data/gfx/2008_BlastDoor_TextureNormal_large.jpg");
	texture2->Create("../data/gfx/stone_wall_normal_map.bmp");
	m_Textures.push_back(texture2);
	// texture3->Create("../data/gfx/2008_BlastDoor_TextureSpec_large.jpg");
	texture3->Create("../data/gfx/specular_map.jpg");
	m_Textures.push_back(texture3);


	m_Shader = new Shader();
	m_Shader->Create("../data/shader/test.vs", "../data/shader/test.fs");
	std::cout << m_Shader->DebugInfo() << std::endl;
	
	for (int i = 0; i < 10; i++) {
		WorldObject o;
		o.SetMesh(m_Mesh);
		o.SetTextures(m_Textures);
		o.SetShader(m_Shader);
		o.Move(0.0, 0.0, 0.0);
		
		m_Objects.push_back(o);
	}
	
	m_Cameras.resize(1);
	m_Cameras[0].Move(0.0, 0.0, 500.0);
	
	m_Lights.resize(1);
}


void Scene::Update() {
	static float counter = 0.0;
	counter += 0.01;
		
	Vector3 position;
	position.X = 0.0;	// cos(counter) * 5;
	position.Y = 0.0;	// cos(counter) * 5;
	position.Z = 1.0;	// sin(counter) * 5;
	m_Lights[0].SetPosition(position);
	m_Lights[0].Apply();
	
	// m_Cameras[0].Rotate(0.0, 0.0, 0.1);
	// m_Cameras[0].Move(0.0, 0.0, 1.0);
	
	m_Objects[0].Move(0.5, 0.0, 0.0);
	m_Objects[0].Rotate(0.0, 0.0, 0.5);
}


const std::vector<WorldObject> &Scene::GetRenderData() const {
	return m_Objects;
}


const std::vector<Camera> &Scene::GetCameras() const {
	return m_Cameras;
}


void Scene::Resize(int width, int height) {
	for (unsigned int i = 0; i < m_Cameras.size(); i++) {
		m_Cameras[i].Resize(width, height);
	}
}

