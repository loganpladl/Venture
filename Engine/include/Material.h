#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include <DirectXMath.h>
#include <d3d11.h>
#include "ConstantBufferPerObject.h"

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
		
		bool IsConstantBufferLoaded();
		void CreateConstantBuffer(ID3D11Device* device);
		void BindConstantBuffer(ID3D11DeviceContext* context);
		// Update const buffer with new world transformation matrix
		void UpdateConstantBufferData(DirectX::XMFLOAT4X4 world);
		// Do this immediately before draw call
		void UpdateConstantBuffer(ID3D11DeviceContext* context);
	private:
		VertexShader* m_vertexShader;
		PixelShader* m_pixelShader;
		DirectX::XMFLOAT4 m_color;
		ConstantBufferPerObject m_constBuffer;
	};
}