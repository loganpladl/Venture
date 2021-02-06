#include "../include/ConstantBufferPerObject.h"

namespace Venture {
	void ConstantBufferPerObject::UpdateData(DirectX::XMFLOAT4X4 world) {
		m_data.world = world;

		// Transpose data for HLSL
		DirectX::XMMATRIX w = DirectX::XMLoadFloat4x4(&m_data.world);
		w = DirectX::XMMatrixTranspose(w);
		DirectX::XMStoreFloat4x4(&m_data.world, w);

		m_constantBuffer.UpdateData(m_data);
	}

	/*
	void ConstantBufferPerObject::UpdateData(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 world) {
		// Load view transform
		DirectX::XMMATRIX v = DirectX::XMLoadFloat4x4(&view);
		DirectX::XMMATRIX w = DirectX::XMLoadFloat4x4(&world);

		DirectX::XMMATRIX mat = DirectX::XMMatrixTranspose(
			w *
			v *
			// TODO: Is there a slight distortion at the edges of the screen?
			DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(70), 4.0f / 3.0f, 0.5f, 100.0f)
		);

		DirectX::XMStoreFloat4x4(&m_data.transform, mat);

		m_constantBuffer.UpdateData(m_data);
	}
	*/
}