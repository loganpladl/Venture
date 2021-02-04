#include "../include/MeshInstance.h"
#include "../include/RenderManager.h"

namespace Venture {
	// Submit mesh/material pair for rendering
	void MeshInstance::Update() {
		RenderManager::Submit(m_mesh, m_material);
	}
}