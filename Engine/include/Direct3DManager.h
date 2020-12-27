#pragma once

#include <d3d11.h>
#include "Mesh.h"
#include <DirectXMath.h>

namespace Venture {
	class Direct3DManager {
	public:
		Direct3DManager();
		~Direct3DManager();
		Direct3DManager(const Direct3DManager&) = delete;
		Direct3DManager& operator=(const Direct3DManager&) = delete;
		int Init(HWND window);
		void Present();
		void ClearBuffer(float red, float green, float blue);
		void DrawMesh(Mesh mesh);
		void UpdateViewTransform(DirectX::XMFLOAT4X4 newTransform);
	private:
		ID3D11Device* m_device = nullptr;
		ID3D11DeviceContext* m_context = nullptr;
		// Output from CreateDevice
		D3D_FEATURE_LEVEL m_featureLevel;
		IDXGISwapChain* m_swapChain = nullptr;
		HWND m_window;
		ID3D11RenderTargetView* m_renderTargetView = nullptr;
		ID3D11DepthStencilView* m_depthStencilView = nullptr;
		DirectX::XMFLOAT4X4 m_viewTransform;
	};
}