#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <vector>
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "TextureLayer.hpp"
#include "WorldObject.hpp"

class Scene {
	public:
		Scene();
		virtual ~Scene();
		void Initialize();
		void Update();
		const std::vector<WorldObject> &GetRenderData() const;
		const std::vector<Camera> &GetCameras() const;
		void Resize(int width, int height);
	
	private:
		std::vector<Camera> m_Cameras;
		std::vector<TextureLayer *> m_Textures;
		Mesh *m_Mesh;
		Shader *m_Shader;
		std::vector<WorldObject> m_Objects;
		std::vector<Light> m_Lights;
};

#endif

