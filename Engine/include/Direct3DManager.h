#pragma once

#include <d3d11.h>

namespace Venture {
	class Direct3DManager {
	public:
		Direct3DManager(HWND window);
		~Direct3DManager();
		Direct3DManager(const Direct3DManager&) = delete;
		Direct3DManager& operator=(const Direct3DManager&) = delete;
		int Init();
		void Present();
	private:
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
		// Output from CreateDevice
		D3D_FEATURE_LEVEL m_featureLevel;
		IDXGISwapChain* m_swapChain;
		HWND m_window;
	};
}