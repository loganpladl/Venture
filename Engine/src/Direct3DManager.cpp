#include "../include/Direct3DManager.h"



namespace Venture {
	Direct3DManager::Direct3DManager() {
		m_device = nullptr;
		m_context = nullptr;
		m_featureLevel = D3D_FEATURE_LEVEL_11_1; //default
	}
	int Direct3DManager::Init() {
		D3D_FEATURE_LEVEL levels[] = {
			D3D_FEATURE_LEVEL_9_1,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_11_1
		};

		UINT deviceFlags = 0;

		#if defined(DEBUG)
		deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif


		HRESULT result = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			deviceFlags,
			levels,
			ARRAYSIZE(levels),
			D3D11_SDK_VERSION,
			&m_device,
			&m_featureLevel,
			&m_context
		);

		if (FAILED(result)) {
			// Handle potential device creation failure
		}
		return 0;
	}
}