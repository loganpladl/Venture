#pragma once
#include "Shader.h"
#include <d3d11.h>

namespace Venture {
	class PixelShader : public Shader {
	public:
		PixelShader(std::string path, ID3D11Device* device, ID3D11DeviceContext* context);
		void Bind() override;
		~PixelShader();
	private:
		ID3D11PixelShader* m_pixelShader;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
	};
}