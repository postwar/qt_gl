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
	
	for (unsigned int i = 0; i < 10; i++) {
		RenderData object;
		object.ObjectId = i;
		object.Texture = m_Textures;
		object.MeshId = m_Mesh;
		object.ShaderId = m_Shader;
		
		m_Data.push_back(object);
	}
}


void Scene::Update() {
	static float counter = 0.0;
	counter += 0.01;
		
	float x = cos(counter) * 5;
	float z = sin(counter) * 5;
	
	glEnable(GL_LIGHT0);
	GLfloat position[] = { x, x, z, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
	
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	m_Camera.Rotate(0.0, 0.0, 0.1);
}


const std::vector<RenderData> &Scene::GetRenderData() const {
	return m_Data;
}


void Scene::Resize(int width, int height) {
	m_Camera.Resize(width, height);
}
