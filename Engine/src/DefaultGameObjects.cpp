#include "../include/DefaultGameObjects.h"
#include "../include/FPSCamera.h"

namespace Venture {
	Mesh DefaultGameObjects::Cube::mesh = DefaultMeshes::GetNewCube();

	GameObjectHandle DefaultGameObjects::GetNewCube() {
		return GameObject::Create();
	}

	GameObjectHandle DefaultGameObjects::GetNewFPSCamera() {
		GameObjectHandle handle = GameObject::Create();
		FPSCamera* camera = new FPSCamera(handle.Get());
		handle.Get()->AddComponent(camera);
		return handle;
	}
}