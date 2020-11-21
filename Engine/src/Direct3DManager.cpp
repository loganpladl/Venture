#include "../include/Direct3DManager.h"
#include "../include/FileSystem.h"
#include "../include/Buffer.h"

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

	void Direct3DManager::Triangle() {
		struct Vertex {
			float x;
			float y;
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};

		Vertex vertices[] = {
			{0.0f, .5f, 255, 0, 0, 255},
			{.5f, -.5f, 0, 255, 0, 255},
			{-.5f, -.5f, 0, 0, 255, 255}
		};
		int indices[] = {
			0, 1, 2
		};

		ID3D11Buffer* pVertexBuffer;
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.CPUAccessFlags = 0u;
		bufferDesc.MiscFlags = 0u;
		bufferDesc.ByteWidth = sizeof(vertices);
		bufferDesc.StructureByteStride = sizeof(Vertex);
		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = vertices;
		m_device->CreateBuffer(&bufferDesc, &subData, &pVertexBuffer);

		// Bind vertex buffer
		const UINT stride = sizeof(Vertex);
		const UINT offset = 0;
		m_context->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);

		// Index Buffer
		ID3D11Buffer* pIndexBuffer;
		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.CPUAccessFlags = 0u;
		indexBufferDesc.MiscFlags = 0u;
		indexBufferDesc.ByteWidth = sizeof(indices);
		indexBufferDesc.StructureByteStride = sizeof(int);
		D3D11_SUBRESOURCE_DATA indexSubData = {};
		indexSubData.pSysMem = indices;
		m_device->CreateBuffer(&indexBufferDesc, &indexSubData, &pIndexBuffer);

		// Bind index buffer
		m_context->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Vertex shader
		ID3D11VertexShader* pVertexShader;
		
		File::AsyncOpenReadCloseRequest* request = FileSystem::AsyncOpenReadCloseFile("VertexShader.cso", "rb");
		request->Wait();
		Buffer vertexBuffer = request->GetBuffer();
		size_t vertexBufferSize = request->GetBufferSize();
		m_device->CreateVertexShader(vertexBuffer.GetBuffer(), vertexBufferSize, nullptr, &pVertexShader);
		// Bind vertex shader 
		m_context->VSSetShader(pVertexShader, nullptr, 0);

		// Pixel shader
		ID3D11PixelShader* pPixelShader;

		request = FileSystem::AsyncOpenReadCloseFile("PixelShader.cso", "rb");
		request->Wait();
		Buffer pixelBuffer = request->GetBuffer();
		size_t pixelBufferSize = request->GetBufferSize();
		m_device->CreatePixelShader(pixelBuffer.GetBuffer(), pixelBufferSize, nullptr, &pPixelShader);
		// Bind pixel shader
		m_context->PSSetShader(pPixelShader, nullptr, 0);

		// Input vertex layout
		ID3D11InputLayout* pInputLayout;
		const D3D11_INPUT_ELEMENT_DESC layout[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 8u, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
		m_device->CreateInputLayout(
			layout, 
			sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), 
			vertexBuffer.GetBuffer(), 
			vertexBufferSize, 
			&pInputLayout
		);

		m_context->IASetInputLayout(pInputLayout);

		// Bind render target
		m_context->OMSetRenderTargets(1u, &m_renderTargetView, nullptr);

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

		int numVertices = sizeof(vertices) / sizeof(Vertex);
		int numIndices = sizeof(indices) / sizeof(int);
		m_context->DrawIndexed(numIndices, 0u, 0u);

		pVertexBuffer->Release();
		pIndexBuffer->Release();
		pVertexShader->Release();
		pPixelShader->Release();
		pInputLayout->Release();
	}
}