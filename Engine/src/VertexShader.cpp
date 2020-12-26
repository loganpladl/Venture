#include "../include/VertexShader.h"

namespace Venture {
	VertexShader::VertexShader(std::string path, ID3D11Device* device, ID3D11DeviceContext* context) : 
		Shader(ShaderType::Vertex, path), m_device(device), m_context(context) {
		m_device->CreateVertexShader(m_bytecode.GetBuffer(), m_bytecode.GetBytes(), nullptr, &m_vertexShader);
	}

	VertexShader::~VertexShader() {
		m_vertexShader->Release();
	}
	
	void VertexShader::Bind() {
		m_context->VSSetShader(m_vertexShader, nullptr, 0);
	}
}