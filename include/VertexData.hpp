#ifndef VERTEXDATA_HPP_
#define VERTEXDATA_HPP_

#include <vector>
#include "Vector.hpp"

class VertexData {
	public:
		bool Validate() const;
		unsigned int ElementsPerVertex() const;
		unsigned int VertexSizeInBytes() const;
	
	public:	
		unsigned int VertexCount;
		unsigned int TextureCoordinateCount;
		std::vector<Vector3> Position;
		std::vector<Vector3> Normal;
		std::vector<std::vector<Vector2> > TextureCoordinates;
		std::vector<unsigned short> Indices;
};

#endif
