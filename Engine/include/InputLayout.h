#pragma once
#include <d3d11.h>
#include "../include/Shader.h"

namespace Venture {
	class InputLayout {
	private:
		ID3D11InputLayout* m_inputLayout;
		const D3D11_INPUT_ELEMENT_DESC* m_layoutDesc;
		size_t m_numElements;
		// Vertex layouts for initialization elsewhere
		static const D3D11_INPUT_ELEMENT_DESC s_layout1[2];
	public:
		explicit InputLayout(const D3D11_INPUT_ELEMENT_DESC* layoutDesc, size_t numElements) : m_inputLayout(nullptr), 
			m_layoutDesc(layoutDesc), m_numElements(numElements){}

		~InputLayout() {
			m_inputLayout->Release();
		}

		void Create(ID3D11Device* device, Shader* shader) {
			device->CreateInputLayout(
				m_layoutDesc,
				static_cast<UINT>(m_numElements),
				shader->GetBytecode(),
				shader->GetBytecodeSize(),
				&m_inputLayout
			);
		}

		void Bind(ID3D11DeviceContext* context) {
			context->IASetInputLayout(m_inputLayout);
		}

		// Vertex layout getters
		static const D3D11_INPUT_ELEMENT_DESC* VertexLayout1() {
			return s_layout1;
		}

		bool IsLoaded() {
			return m_inputLayout != nullptr;
		}
	};
}