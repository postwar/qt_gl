#include "Objects.hpp"


VertexData Objects::CreateSquare() {
	VertexData vertices;
	float posX = -200.0; float posY = -200.0;
	float w = 400.0; float h = 400.0;

	float vx1 = posX;	float vx2 = posX + w;
	float vy1 = posY;	float vy2 = posY + h;
	float tx1 = 0.0;	float tx2 = 1.0;
	float ty1 = 0.0;	float ty2 = 1.0;

	vertices.VertexCount = 4;
	vertices.TextureCoordinateCount = 2;
	
	vertices.Position.resize(4);
	vertices.Normal.resize(4);
	vertices.TextureCoordinates.resize(4);
	for (int i = 0; i < 4; i++) {
		vertices.TextureCoordinates[i].resize(2);
	}

	vertices.Position[0].X = vx1;	vertices.Position[0].Y = vy1;	vertices.Position[0].Z = 0.0;
	vertices.Normal[0].X   = 0.0;	vertices.Normal[0].Y   = 0.0;	vertices.Normal[0].Z   = 1.0;
	vertices.TextureCoordinates[0][0].X = tx1;	vertices.TextureCoordinates[0][0].Y = ty1;
	vertices.TextureCoordinates[0][1].X = tx1;	vertices.TextureCoordinates[0][1].Y = ty1;

	vertices.Position[1].X = vx2;	vertices.Position[1].Y = vy1;	vertices.Position[1].Z = 0.0;
	vertices.Normal[1].X   = 0.0;	vertices.Normal[1].Y   = 0.0;	vertices.Normal[1].Z   = 1.0;
	vertices.TextureCoordinates[1][0].X = tx2;	vertices.TextureCoordinates[1][0].Y = ty1;
	vertices.TextureCoordinates[1][1].X = tx2;	vertices.TextureCoordinates[1][1].Y = ty1;

	vertices.Position[2].X = vx2;	vertices.Position[2].Y = vy2;	vertices.Position[2].Z = 0.0;
	vertices.Normal[2].X   = 0.0;	vertices.Normal[2].Y   = 0.0;	vertices.Normal[2].Z   = 1.0;
	vertices.TextureCoordinates[2][0].X = tx2;	vertices.TextureCoordinates[2][0].Y = ty2;
	vertices.TextureCoordinates[2][1].X = tx2;	vertices.TextureCoordinates[2][1].Y = ty2;

	vertices.Position[3].X = vx1;	vertices.Position[3].Y = vy2;	vertices.Position[3].Z = 0.0;
	vertices.Normal[3].X   = 0.0;	vertices.Normal[3].Y   = 0.0;	vertices.Normal[3].Z   = 1.0;
	vertices.TextureCoordinates[3][0].X = tx1;	vertices.TextureCoordinates[3][0].Y = ty2;
	vertices.TextureCoordinates[3][1].X = tx1;	vertices.TextureCoordinates[3][1].Y = ty2;

	vertices.Indices.resize(6);
	vertices.Indices[0] = 0;
	vertices.Indices[1] = 1;
	vertices.Indices[2] = 2;
	vertices.Indices[3] = 2;
	vertices.Indices[4] = 3;
	vertices.Indices[5] = 0;

	return vertices;
}

