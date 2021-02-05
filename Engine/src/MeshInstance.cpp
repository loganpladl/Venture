#include "../include/MeshInstance.h"
#include "../include/RenderManager.h"
#include "../include/GameObject.h"
#include "../include/Transform.h"

namespace Venture {
	// Submit mesh/material pair for rendering
	void MeshInstance::Update() {
		GameObject* object = GetGameObject();

		// Update model to world transformation matrix
		m_worldTransform = object->GetTransform()->ObjectToWorld();

		RenderManager::Submit(m_mesh, m_material, m_worldTransform);
	}
}