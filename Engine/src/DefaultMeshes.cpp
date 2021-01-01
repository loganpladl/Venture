#include "../include/DefaultMeshes.h"

namespace Venture {
	// Initialize static mesh data
	std::vector<Vertex> DefaultMeshes::Cube::vertices = {
			{ 1, 1, 1,  	0, 0, 0},
			{ -1, 1, 1,		255, 0, 0 },
			{ 1, -1, 1,		0, 255, 0},
			{ 1, 1, -1,		255, 255, 0},
			{ -1, -1, 1,	0, 0, 255},
			{ 1, -1, -1,	255, 0, 255},
			{ -1, 1, -1,	0, 255, 255},
			{ -1, -1, -1,	255, 255, 255}
	};

	std::vector<int> DefaultMeshes::Cube::indices = {
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

	Mesh* DefaultMeshes::s_cube = new Mesh(Cube::vertices, Cube::indices);

	Mesh* DefaultMeshes::GetCube() {
		return s_cube;
	}
}