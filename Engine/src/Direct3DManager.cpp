#include "../include/Direct3DManager.h"
#include "../include/FileSystem.h"
#include "../include/Buffer.h"
#include <cmath>
#include <DirectxMath.h>
#include "../include/Mesh.h"
#include "../include/Vertex.h"
#include "../include/VertexShader.h"
#include "../include/PixelShader.h"

//temp
#include "../include/Time.h"

namespace Venture {
	Direct3DManager::Direct3DManager() : m_viewTransform(), m_projectionTransform() {
		m_featureLevel = D3D_FEATURE_LEVEL_11_1; //default
		m_window = nullptr;
	}
	int Direct3DManager::Init(HWND window) {
		m_window = window;

		D3D_FEATURE_LEVEL levels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		UINT deviceFlags = 0;

		#if defined(_DEBUG)
		deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif

		// Initialization parameters for swap chain
		DXGI_SWAP_CHAIN_DESC swapChainDescription;
		ZeroMemory(&swapChainDescription, sizeof(swapChainDescription));
		// Match width and height to window
		swapChainDescription.BufferDesc.Width = 0;
		swapChainDescription.BufferDesc.Height = 0;
		swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		// Used default refresh rate
		swapChainDescription.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDescription.BufferDesc.RefreshRate.Denominator = 0;
		// Shouldn't require scaling since width and height should equal window
		swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDescription.SampleDesc.Count = 1;
		// No antialiasing for now
		swapChainDescription.SampleDesc.Quality = 0;
		swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDescription.BufferCount = 2;
		swapChainDescription.OutputWindow = m_window;
		swapChainDescription.Windowed = TRUE;
		swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDescription.Flags = 0;


		HRESULT result = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			deviceFlags,
			levels,
			ARRAYSIZE(levels),
			D3D11_SDK_VERSION,
			&swapChainDescription,
			&m_swapChain,
			&m_device,
			&m_featureLevel,
			&m_context
		);

		ID3D11Resource* backBuffer = nullptr;
		m_swapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBuffer));
		if (backBuffer != 0) {
			m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
		}
		backBuffer->Release();

		// Depth-stencil state
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		ID3D11DepthStencilState* pDSState;
		m_device->CreateDepthStencilState(&dsDesc, &pDSState);

		// Bind depth state
		m_context->OMSetDepthStencilState(pDSState, 1u);

		// Depth-stencil texture
		ID3D11Texture2D* pDepthStencil;
		D3D11_TEXTURE2D_DESC depthDesc = {};
		// Match height and width of swap chain
		DXGI_SWAP_CHAIN_DESC pSCDesc;
		m_swapChain->GetDesc(&pSCDesc);
		depthDesc.Width = pSCDesc.BufferDesc.Width;
		depthDesc.Height = pSCDesc.BufferDesc.Height;
		depthDesc.MipLevels = 1u;
		depthDesc.ArraySize = 1u;
		depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthDesc.SampleDesc.Count = 1u;
		depthDesc.SampleDesc.Quality = 0u;
		depthDesc.Usage = D3D11_USAGE_DEFAULT;
		depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		m_device->CreateTexture2D(&depthDesc, nullptr, &pDepthStencil);

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0u;

		if (pDepthStencil != nullptr) {
			m_device->CreateDepthStencilView(pDepthStencil, &dsvDesc, &m_depthStencilView);
		}
		else {
			// TODO: Handle error if depth stencil texture was not successfully created
		}
		
		m_context->OMSetRenderTargets(1u, &m_renderTargetView, m_depthStencilView);

		if (FAILED(result)) {
			// Handle potential device creation failure
		}

		// TODO:: Default projection matrix, should create and update based on window dimensions
		DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(70), 4.0f / 3.0f, 0.5f, 100.0f);
		DirectX::XMStoreFloat4x4(&m_projectionTransform, proj);
		CreateConstBuffers();
		UpdateConstBufferResizeData();
		UpdateConstBufferResize();

		return 0;
	}
	Direct3DManager::~Direct3DManager() {
		if (m_device != nullptr) {
			m_device->Release();
		}
		if (m_context != nullptr) {
			m_context->Release();
		}
		if (m_swapChain != nullptr) {
			m_swapChain->Release();
		}
		if (m_renderTargetView != nullptr) {
			m_renderTargetView->Release();
		}
	}

	void Direct3DManager::Present() {
		m_swapChain->Present(1u, 0u);
	}

	void Direct3DManager::ClearBuffer(float red, float green, float blue) {
		const float color[] = { red, green, blue, 1.0f };
		m_context->ClearRenderTargetView(m_renderTargetView, color);
		m_context->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0u);
	}

	void Direct3DManager::DrawMeshMaterial(Mesh* mesh, Material* material, DirectX::XMFLOAT4X4 worldTransform) {
		if (!mesh->IsLoaded()) {
			mesh->CreateBuffers(m_device);
		}
		mesh->BindBuffers(m_context);

		// Create and bind shaders
		if (!material->ShadersLoaded()) {
			material->CreateShaders(m_device);
		}
		material->BindShaders(m_context);
		
		// Create and bind constant buffer
		if (!material->IsConstantBufferLoaded()) {
			material->CreateConstantBuffer(m_device);
		}
		material->BindConstantBuffer(m_context);

		// Update constant buffer with world transform of this object
		material->UpdateConstantBufferData(worldTransform);
		material->UpdateConstantBuffer(m_context);


		if (!AreConstBuffersLoaded()) {
			CreateConstBuffers();
		}
		BindConstBuffers();

		UpdateConstBufferPerFrameData();
		UpdateConstBufferPerFrame();

		// Input vertex layout
		ID3D11InputLayout* pInputLayout;
		const D3D11_INPUT_ELEMENT_DESC layout[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
		m_device->CreateInputLayout(
			layout, 
			sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), 
			material->GetVertexShader()->GetBytecode(), 
			material->GetVertexShader()->GetBytecodeSize(),
			&pInputLayout
		);

		m_context->IASetInputLayout(pInputLayout);

		// Bind render target
		// Note: Must repeat every frame since we're using DXGI_SWAP_EFFECT_FLIP_DISCARD
		m_context->OMSetRenderTargets(1u, &m_renderTargetView, m_depthStencilView);

		// Viewport configuration
		D3D11_VIEWPORT vp;
		vp.Width = 640;
		vp.Height = 480;
		vp.MinDepth = 0;
		vp.MaxDepth = 1;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_context->RSSetViewports(1u, &vp);

		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		int numIndices = mesh->NumIndices();
		m_context->DrawIndexed(numIndices, 0u, 0u);

		pInputLayout->Release();
	}

	void Direct3DManager::UpdateViewTransform(DirectX::XMFLOAT4X4 newTransform) {
		m_viewTransform = newTransform;
	}

	void Direct3DManager::UpdateProjectionTransform(DirectX::XMFLOAT4X4 newTransform) {
		m_projectionTransform = newTransform;
	}

	void Direct3DManager::UpdateConstBufferPerFrame() {
		m_constBufferPerFrame.Update(m_context);
	}

	void Direct3DManager::UpdateConstBufferResize() {
		m_constBufferResize.Update(m_context);
	}

	void Direct3DManager::UpdateConstBufferPerFrameData() {
		m_constBufferPerFrame.UpdateData(m_viewTransform);
	}

	void Direct3DManager::UpdateConstBufferResizeData() {
		m_constBufferResize.UpdateData(m_projectionTransform);
	}

	void Direct3DManager::CreateConstBuffers() {
		m_constBufferPerFrame.Create(m_device);
		m_constBufferResize.Create(m_device);
	}
	void Direct3DManager::BindConstBuffers() {
		m_constBufferPerFrame.Bind(m_context);
		m_constBufferResize.Bind(m_context);
	}
	bool Direct3DManager::AreConstBuffersLoaded() {
		return m_constBufferPerFrame.IsLoaded() && m_constBufferResize.IsLoaded();
	}
}