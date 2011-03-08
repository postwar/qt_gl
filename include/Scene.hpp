#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <vector>
#include "Camera.hpp"
#include "Mesh.hpp"
#include "RenderData.hpp"
#include "Shader.hpp"
#include "TextureLayer.hpp"

class Scene {
	public:
		Scene();
		virtual ~Scene();
		void Initialize();
		void Update();
		const std::vector<RenderData> &GetRenderData() const;
		void Resize(int width, int height);
	
	private:
		Camera m_Camera;
		std::vector<RenderData> m_Data;
		std::vector<TextureLayer *> m_Textures;
		Mesh *m_Mesh;
		Shader *m_Shader;
};

#endif

