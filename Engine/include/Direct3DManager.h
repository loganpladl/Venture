#pragma once

#include <d3d11.h>
#include "Mesh.h"
#include "Material.h"
#include <DirectXMath.h>
#include "ConstantBufferPerFrame.h"
#include "ConstantBufferResize.h"

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
		void DrawMeshMaterial(Mesh* mesh, Material* material, DirectX::XMFLOAT4X4 worldTransform);
		void UpdateViewTransform(DirectX::XMFLOAT4X4 newTransform);
		void UpdateProjectionTransform(DirectX::XMFLOAT4X4 newTransform);

		void UpdateConstBufferPerFrameData();
		void UpdateConstBufferPerFrame();
		void UpdateConstBufferResizeData();
		void UpdateConstBufferResize();
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
		DirectX::XMFLOAT4X4 m_projectionTransform;

		ConstantBufferPerFrame m_constBufferPerFrame;
		ConstantBufferResize m_constBufferResize;

		D3D11_VIEWPORT m_viewport;

		// Bind per frame and per resize const buffers
		void CreateConstBuffers();
		void BindConstBuffers();
		bool AreConstBuffersLoaded();
	};
}