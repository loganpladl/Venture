#include "../include/RenderManager.h"
#include "../include/Time.h"

#include "../include/DefaultMeshes.h"

namespace Venture {
	// TODO: Decide whether to make everything static or not
	DirectX::XMFLOAT4X4 RenderManager::m_viewTransform;

	std::vector<std::tuple<Mesh*, Material*, DirectX::XMFLOAT4X4>> RenderManager::s_renderables;

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

		for (const std::tuple<Mesh*, Material*, DirectX::XMFLOAT4X4>& meshMaterial : s_renderables) {
			m_direct3DManager.DrawMeshMaterial(std::get<0>(meshMaterial), std::get<1>(meshMaterial), std::get<2>(meshMaterial));
		}

		m_direct3DManager.Present();
	}

	// Submit mesh/material pairs for upcoming draw call
	void RenderManager::Submit(Mesh* mesh, Material* material, DirectX::XMFLOAT4X4 worldTransform) {
		s_renderables.push_back(std::tuple<Mesh*, Material*, DirectX::XMFLOAT4X4>(mesh, material, worldTransform));
	}

	void RenderManager::Clear() {
		s_renderables.clear();
	}
}