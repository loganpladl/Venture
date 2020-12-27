#include "../include/DefaultGameObjects.h"

namespace Venture {
	Mesh DefaultGameObjects::Cube::mesh = DefaultMeshes::GetNewCube();

	GameObjectHandle DefaultGameObjects::GetNewCube() {
		return GameObject::Create();
	}
}