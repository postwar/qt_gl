#ifndef RENDERDATA_HPP_
#define RENDERDATA_HPP_

#include <vector>
#include "Shader.hpp"
#include "TextureLayer.hpp"
#include "Mesh.hpp"

struct RenderData {
	unsigned int ObjectId;
	std::vector<TextureLayer *> Texture;
	Shader *ShaderId;
	Mesh *MeshId;
};

#endif
