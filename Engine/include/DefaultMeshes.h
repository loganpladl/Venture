#pragma once
#include "Mesh.h"

namespace Venture {
	class DefaultMeshes {
	private:
		// Vertex and index data for cube with side length 1
		struct Cube {
			static std::vector<Vertex> vertices;
			static std::vector<int> indices;
		};
		static Mesh* s_cube;
	public:
		// Returns the same static mesh for each call
		static Mesh* GetCube();
	};
}