#pragma once

#include <d3d11.h>

namespace Venture {
	class Direct3DManager {
	public:
		Direct3DManager();
		int Init();
	private:
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
		D3D_FEATURE_LEVEL m_featureLevel;
	};
}