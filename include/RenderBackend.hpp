#ifndef RENDERBACKEND_HPP_
#define RENDERBACKEND_HPP_

#include <GL/glew.h>
#include <vector>
/*
#include <GL/gl.h>
#include <GL/glext.h>
*/
#include "RenderData.hpp"
#include "Rect.hpp"
#include "Shader.hpp"

class RenderBackend {
	public:
		RenderBackend();
		virtual ~RenderBackend();
		void Initialize();
		void StartFrame();
		void PushRenderData(const RenderData &data);
		void Render();
		void RenderSelect();
		const std::vector<unsigned int> &Select(const Rect &area);
		void EndFrame();
	
	private:
		void ClearScreen();
	
	private:
		std::vector<RenderData> m_RenderData;
		std::vector<unsigned int> m_Selection;
		std::vector<GLuint> m_SelectionBuffer;
		Shader m_Shader;
		static const int BUFFER_SIZE;
};

#endif
