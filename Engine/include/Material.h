#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include <DirectXMath.h>
#include <d3d11.h>

namespace Venture {

	class Material {
	public:
		Material();
		Material(DirectX::XMFLOAT4 color);
		bool ShadersLoaded();
		void CreateShaders(ID3D11Device* device);
		void BindShaders(ID3D11DeviceContext* context);
		VertexShader* GetVertexShader();
		PixelShader* GetPixelShader();
	private:
		VertexShader* m_vertexShader;
		PixelShader* m_pixelShader;
		DirectX::XMFLOAT4 m_color;
	};

}