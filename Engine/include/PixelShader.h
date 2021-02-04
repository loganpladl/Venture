#pragma once
#include "Shader.h"
#include <d3d11.h>

namespace Venture {
	class PixelShader : public Shader {
	public:
		PixelShader(std::string path);
		void Create(ID3D11Device* device) override;
		void Bind(ID3D11DeviceContext* context) override;
		bool IsLoaded() override;
		~PixelShader();
	private:
		ID3D11PixelShader* m_pixelShader;
	};
}