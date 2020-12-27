#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "DefaultMeshes.h"


namespace Venture {
	class DefaultGameObjects {
	private:
		struct Cube {
			static Mesh mesh;
		};
	public:
		static GameObjectHandle GetNewCube();
	};
}