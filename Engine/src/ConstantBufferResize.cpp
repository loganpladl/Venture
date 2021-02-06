#include "../include/ConstantBufferResize.h"

namespace Venture {
	void ConstantBufferResize::UpdateData(DirectX::XMFLOAT4X4 projection) {
		m_data.projection = projection;

		// Transpose data for HLSL
		DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&m_data.projection);
		proj = DirectX::XMMatrixTranspose(proj);
		DirectX::XMStoreFloat4x4(&m_data.projection, proj);

		m_constantBuffer.UpdateData(m_data);
	}
}