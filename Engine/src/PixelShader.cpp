#include "../include/PixelShader.h"

namespace Venture {
	PixelShader::PixelShader(std::string path) :
		Shader(ShaderType::Pixel, path), m_pixelShader(nullptr) {
	}

	PixelShader::~PixelShader() {
		m_pixelShader->Release();
	}

	void PixelShader::Create(ID3D11Device* device) {
		if (m_bytecode.IsNull()) {
			ReadFile();
		}
		device->CreatePixelShader(m_bytecode.GetBuffer(), m_bytecode.GetBytes(), nullptr, &m_pixelShader);
	}

	void PixelShader::Bind(ID3D11DeviceContext* context) {
		context->PSSetShader(m_pixelShader, nullptr, 0);
	}

	bool PixelShader::IsLoaded() {
		return m_pixelShader != nullptr;
	}
}