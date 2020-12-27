#pragma once
#include "Direct3DManager.h"
#include <DirectXMath.h>

namespace Venture {
	class RenderManager {
	// TODO: Fix static/nonstatic i.e. refactor
	private:
		Direct3DManager m_direct3DManager;
		HWND m_window;
		static DirectX::XMFLOAT4X4 m_viewTransform;
	public:
		RenderManager();
		int Init(HWND window);
		void Render();
		static inline void UpdateViewTransform(DirectX::XMFLOAT4X4 newTransform) { m_viewTransform = newTransform; }
	};
}