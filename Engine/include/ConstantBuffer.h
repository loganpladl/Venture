#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

namespace Venture {
	// Abstract interface, define constant buffer data in derived classes
	template <class T>
	class ConstantBuffer {
	private:
		T m_data;
		unsigned int m_slot;
		ID3D11Buffer* m_constantBuffer;
	public:
		explicit ConstantBuffer(T data, unsigned int slot) : m_data(data), m_slot(slot), m_constantBuffer(nullptr) {}
		~ConstantBuffer() {
			m_constantBuffer->Release();
		}

		void UpdateData(T data) {
			m_data = data;
		}

		void Update(ID3D11DeviceContext* context) {
			context->UpdateSubresource(m_constantBuffer, 0, nullptr, &m_data, 0, 0);
		}

		inline bool IsLoaded() {
			return (m_constantBuffer != nullptr);
		}

		void Create(ID3D11Device* device) {
			D3D11_BUFFER_DESC cbd;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			// Can only use UpdateSubresource with D3D11_USAGE_DEFAULT
			cbd.Usage = D3D11_USAGE_DEFAULT;
			//cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.CPUAccessFlags = 0u;
			cbd.MiscFlags = 0u;
			cbd.ByteWidth = sizeof(m_data);
			cbd.StructureByteStride = 0u;
			D3D11_SUBRESOURCE_DATA csd = {};
			csd.pSysMem = &m_data;
			device->CreateBuffer(&cbd, &csd, &m_constantBuffer);
		}

		void Bind(ID3D11DeviceContext* context) {
			// bind constant buffer to vertex shader
			context->VSSetConstantBuffers(m_slot, 1u, &m_constantBuffer);
		}
	};
}