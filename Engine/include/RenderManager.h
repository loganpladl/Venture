#pragma once
#include "Direct3DManager.h"
#include <DirectXMath.h>
#include "../include/CircularQueue.h"
#include <utility> // for std::pair
#include "Mesh.h"
#include "Material.h"
#include <vector>

namespace Venture {
	class RenderManager {
	// TODO: Fix static/nonstatic i.e. refactor
	private:
		static std::vector<std::pair<Mesh*, Material*>> s_renderables;
		Direct3DManager m_direct3DManager;
		HWND m_window;
		static DirectX::XMFLOAT4X4 m_viewTransform;
	public:
		RenderManager();
		int Init(HWND window);
		// Render frame and clear all submitted mesh/material pairs
		void Render();
		static inline void UpdateViewTransform(DirectX::XMFLOAT4X4 newTransform) { 
			m_viewTransform = newTransform;
		}
		// Submit mesh/material pairs for draw call
		static void Submit(Mesh*, Material*);
		// Clear mesh/materials for next draw call
		static void Clear();
	};
}