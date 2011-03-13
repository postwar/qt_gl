#ifndef RENDERBACKEND_HPP_
#define RENDERBACKEND_HPP_

#include <GL/glew.h>
#include <vector>
#include "Camera.hpp"
#include "WorldObject.hpp"
#include "Rect.hpp"
#include "RenderTarget.hpp"
#include "Shader.hpp"

class RenderTexture;

class RenderBackend {
	public:
		RenderBackend();
		virtual ~RenderBackend();
		void Initialize();
		void StartFrame();
		void PushRenderData(const WorldObject &data);
		void PushCamera(const Camera &camera);
		void Render();
		void RenderSelect();
		const std::vector<unsigned int> &Select(const Rect &area);
		void EndFrame();
	
	private:
		void ClearScreen();
	
	private:
		std::vector<WorldObject> m_RenderData;
		std::vector<Camera> m_Cameras;
		std::vector<unsigned int> m_Selection;
		std::vector<GLuint> m_SelectionBuffer;
		Shader m_SelectionShader;
		std::vector<RenderTexture *> m_RenderTextures;
		RenderTexture *m_DepthTexture;
		RenderTarget m_RenderTarget;
		Shader m_DeferredShader;
		static const int BUFFER_SIZE;
};

#endif
