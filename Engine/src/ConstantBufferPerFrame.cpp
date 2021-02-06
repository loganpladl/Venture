#include "../include/ConstantBufferPerFrame.h"

namespace Venture {
	void ConstantBufferPerFrame::UpdateData(DirectX::XMFLOAT4X4 view) {
		m_data.view = view;

		// Transpose data for HLSL
		DirectX::XMMATRIX v = DirectX::XMLoadFloat4x4(&m_data.view);
		v = DirectX::XMMatrixTranspose(v);
		DirectX::XMStoreFloat4x4(&m_data.view, v);

		m_constantBuffer.UpdateData(m_data);
	}
}