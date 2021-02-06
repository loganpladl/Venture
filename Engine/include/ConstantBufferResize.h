#pragma once

#include "ConstantBuffer.h"
#include <d3d11.h>

namespace Venture {
// Constant Buffer to be updated when window is resized
	class ConstantBufferResize {
	private:
		// Composition instead of inheritance since ConstantBuffer data is of variable type
		struct ConstantBufferType {
			// Projection matrix
			DirectX::XMFLOAT4X4 projection;
		} m_data;
		ConstantBuffer<ConstantBufferType> m_constantBuffer;
	public:
		ConstantBufferResize() : m_data(), m_constantBuffer(ConstantBuffer<ConstantBufferType>(m_data, 2)) {}
		void UpdateData(DirectX::XMFLOAT4X4 projection);
		bool IsLoaded() {
			return m_constantBuffer.IsLoaded();
		}
		void Create(ID3D11Device* device) {
			m_constantBuffer.Create(device);
		}
		void Bind(ID3D11DeviceContext* context) {
			m_constantBuffer.Bind(context);
		}
		// Update 
		void Update(ID3D11DeviceContext* context) {
			m_constantBuffer.Update(context);
		}
	};
}