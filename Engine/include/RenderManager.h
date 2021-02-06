#pragma once
#include "Direct3DManager.h"
#include <DirectXMath.h>
#include "../include/CircularQueue.h"
#include <utility>
#include <tuple>
#include "Mesh.h"
#include "Material.h"
#include <vector>

namespace Venture {
	class RenderManager {
	// TODO: Fix static/nonstatic i.e. refactor
	private:
		static std::vector<std::tuple<Mesh*, Material*, DirectX::XMFLOAT4X4>> s_renderables;
		Direct3DManager m_direct3DManager;
		HWND m_window;
		static DirectX::XMFLOAT4X4 m_viewTransform;
		static DirectX::XMFLOAT4X4 m_projectionTransform;
	public:
		RenderManager();
		int Init(HWND window);
		// Render frame and clear all submitted mesh/material pairs
		void Render();
		static inline void UpdateViewTransform(DirectX::XMFLOAT4X4 newTransform) { 
			m_viewTransform = newTransform;
		}
		static inline void UpdateProjectionTransform(DirectX::XMFLOAT4X4 newTransform) {
			m_projectionTransform = newTransform;
		}
		// Submit mesh/material pairs for draw call
		static void Submit(Mesh*, Material*, DirectX::XMFLOAT4X4 worldTransform);
		// Clear mesh/materials for next draw call
		static void Clear();
	};
}