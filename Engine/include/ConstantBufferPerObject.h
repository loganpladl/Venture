#pragma once
#include "ConstantBuffer.h"
#include <DirectXMath.h>
#include <d3d11.h>

namespace Venture {
	// Constant buffer data to be updated per mesh instance
	class ConstantBufferPerObject {
	private:
		// Composition instead of inheritance since ConstantBuffer data is of variable type
		struct ConstantBufferType {
			// Object to world transformation matrix
			DirectX::XMFLOAT4X4 world;
		} m_data;
		ConstantBuffer<ConstantBufferType> m_constantBuffer;
	public:
		ConstantBufferPerObject() : m_data(), m_constantBuffer(ConstantBuffer<ConstantBufferType>(m_data, 0)){}
		void UpdateData(DirectX::XMFLOAT4X4 world);
		bool IsLoaded() {
			return m_constantBuffer.IsLoaded();
		}
		void Create(ID3D11Device* device) {
			m_constantBuffer.Create(device);
		}
		void Bind(ID3D11DeviceContext* context) {
			m_constantBuffer.Bind(context);
		}
		// Update constant buffer subresource data
		void Update(ID3D11DeviceContext* context) {
			m_constantBuffer.Update(context);
		}
	};
}