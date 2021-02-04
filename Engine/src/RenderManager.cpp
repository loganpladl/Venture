#include "../include/RenderManager.h"
#include "../include/Time.h"

#include "../include/DefaultMeshes.h"

namespace Venture {
	// TODO: Decide whether to make everything static or not
	DirectX::XMFLOAT4X4 RenderManager::m_viewTransform;

	std::vector<std::pair<Mesh*, Material*>> RenderManager::s_renderables;

	RenderManager::RenderManager() {
		m_window = nullptr;
		m_direct3DManager;
	}

	int RenderManager::Init(HWND window) {
		int error = m_direct3DManager.Init(window);
		return error;
	}

	void RenderManager::Render() {
		m_direct3DManager.UpdateViewTransform(m_viewTransform);
		m_direct3DManager.ClearBuffer(0.0f, 0.0f, 0.0f);

		for (const std::pair<Mesh*, Material*>& meshMaterial : s_renderables) {
			m_direct3DManager.DrawMeshMaterial(meshMaterial.first, meshMaterial.second);
		}

		m_direct3DManager.Present();
	}

	// Submit mesh/material pairs for upcoming draw call
	void RenderManager::Submit(Mesh* mesh, Material* material) {
		s_renderables.push_back(std::pair<Mesh*, Material*>(mesh, material));
	}

	void RenderManager::Clear() {
		s_renderables.clear();
	}
}