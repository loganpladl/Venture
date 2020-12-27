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
	public:
		static Mesh GetNewCube();
	};
}