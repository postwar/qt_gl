#include "VertexData.hpp"


bool VertexData::Validate() const {
	if (VertexCount != Position.size()) return false;
	if (VertexCount != Normal.size()) return false;
	if (VertexCount != TextureCoordinates.size()) return false;
	
	for (unsigned int i = 0; i < VertexCount; i++) {
		if (TextureCoordinateCount != TextureCoordinates[i].size()) return false;
	}
	
	return true;	
}


unsigned int VertexData::ElementsPerVertex() const {
	int positionSize = 3;
	int normalSize = 3;
	int textureSize = 2;
	int vertexSize = (positionSize + normalSize + (textureSize * TextureCoordinateCount)) * VertexCount;
	
	return vertexSize;
}


unsigned int VertexData::VertexSizeInBytes() const {
	return ElementsPerVertex() * sizeof(float);
}

