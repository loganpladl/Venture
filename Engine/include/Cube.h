#pragma once
#include "Vertex.h"

// Cube with clockwise winding order, left handed coordinate system
namespace Venture {
	class Cube {
	public:
		Cube(float sideLength) {
			float vertexPos = sideLength / 2;
			vertices[0] = { vertexPos, vertexPos, vertexPos }; // top right forward
			vertices[1] = { -vertexPos, vertexPos, vertexPos }; // top left forward
			vertices[2] = { vertexPos, -vertexPos, vertexPos }; // bottom right forward
			vertices[3] = { vertexPos, vertexPos, -vertexPos }; // top right back
			vertices[4] = { -vertexPos, -vertexPos, vertexPos }; // bottom left forward
			vertices[5] = { vertexPos, -vertexPos, -vertexPos }; // bottom right back
			vertices[6] = { -vertexPos, vertexPos, -vertexPos }; // top left back
			vertices[7] = { -vertexPos, -vertexPos, -vertexPos }; // bottom left back
		}
		Vertex* Vertices() {
			return vertices;
		}
		int* Indices() {
			return indices;
		}
		// Cube always has 8 vertices
		size_t NumVertices() {
			return 8;
		}
		// Cube always has 12 triangles + 3 indices per triangle = 36 indices total
		size_t NumIndices() {
			return 12 * 3;
		}

	private:
		Vertex vertices[8];
		int indices[12*3] = {
			0, 3, 1,	//top face
			3, 6, 1,	//top face
			3, 5, 6,	//front face
			5, 7, 6,	//front face
			0, 2, 3,	// right face
			2, 5, 3,	// right face
			1, 6, 4,	// left face
			6, 7, 4,	// left face
			0, 1, 2,	// back face
			1, 4, 2,	// back face
			2, 4, 5,	// bottom face
			4, 7, 5,	// bottom face
		};
	};
}