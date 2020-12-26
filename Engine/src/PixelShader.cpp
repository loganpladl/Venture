#include "../include/PixelShader.h"

namespace Venture {
	PixelShader::PixelShader(std::string path, ID3D11Device* device, ID3D11DeviceContext* context) :
		Shader(ShaderType::Pixel, path), m_device(device), m_context(context) {
		m_device->CreatePixelShader(m_bytecode.GetBuffer(), m_bytecode.GetBytes(), nullptr, &m_pixelShader);
	}

	PixelShader::~PixelShader() {
		m_pixelShader->Release();
	}

	void PixelShader::Bind() {
		m_context->PSSetShader(m_pixelShader, nullptr, 0);
	}
}