#include "../include/Direct3DManager.h"

namespace Venture {
	Direct3DManager::Direct3DManager() {
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
		swapChainDescription.BufferCount = 1;
		swapChainDescription.OutputWindow = m_window;
		swapChainDescription.Windowed = TRUE;
		swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
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

		if (FAILED(result)) {
			// Handle potential device creation failure
		}
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
	}
}