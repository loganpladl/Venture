#include "../include/DefaultGameObjects.h"
#include "../include/FPSCamera.h"
#include "../include/Mesh.h"
#include "../include/DefaultMeshes.h"
#include "../include/MeshInstance.h"
#include "../include/Transform.h"
#include "../include/DefaultMaterials.h"

namespace Venture {
	GameObjectHandle DefaultGameObjects::GetNewCube() {
		GameObjectHandle handle = GameObject::Create();
		Transform* transform = new Transform(handle.Get());
		handle.Get()->AddComponent(transform);
		MeshInstance* cube = new MeshInstance(handle.Get(), DefaultMeshes::GetCube(), DefaultMaterials::UnlitWhite());
		handle.Get()->AddComponent(cube);
		return handle;
	}

	GameObjectHandle DefaultGameObjects::GetNewFPSCamera() {
		GameObjectHandle handle = GameObject::Create();
		Transform* transform = new Transform(handle.Get());
		handle.Get()->AddComponent(transform);
		// Create FPS Camera component, TODO: doesn't currently use transform, should fix.
		FPSCamera* camera = new FPSCamera(handle.Get());
		handle.Get()->AddComponent(camera);
		return handle;
	}
}