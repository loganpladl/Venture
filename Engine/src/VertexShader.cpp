#include "../include/VertexShader.h"

namespace Venture {
	VertexShader::VertexShader(std::string path) : 
		Shader(ShaderType::Vertex, path), m_vertexShader(nullptr) {
	}

	VertexShader::~VertexShader() {
		m_vertexShader->Release();
	}

	void VertexShader::Create(ID3D11Device* device) {
		if (m_bytecode.IsNull()) {
			ReadFile();
		}
		device->CreateVertexShader(m_bytecode.GetBuffer(), m_bytecode.GetBytes(), nullptr, &m_vertexShader);
	}
	
	void VertexShader::Bind(ID3D11DeviceContext* context) {
		context->VSSetShader(m_vertexShader, nullptr, 0);
	}

	bool VertexShader::IsLoaded() {
		return m_vertexShader != nullptr;
	}
}