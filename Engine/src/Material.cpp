#include "../include/Material.h"
#include "../include/DefaultShaders.h"

namespace Venture {
	// Default constructor uses unlit shaders and pure white color
	Material::Material() : m_vertexShader(DefaultShaders::VertexUnlit()), m_pixelShader(DefaultShaders::PixelUnlit()), m_color(1,1,1,1) {

	}

	Material::Material(DirectX::XMFLOAT4 color) : m_vertexShader(DefaultShaders::VertexUnlit()), m_pixelShader(DefaultShaders::PixelUnlit()), m_color(color) {

	}

	void Material::CreateShaders(ID3D11Device* device) {
		m_vertexShader->Create(device);
		m_pixelShader->Create(device);
	}

	void Material::BindShaders(ID3D11DeviceContext* context) {
		m_vertexShader->Bind(context);
		m_pixelShader->Bind(context);
	}

	bool Material::ShadersLoaded() {
		return m_vertexShader->IsLoaded() && m_pixelShader->IsLoaded();
	}

	VertexShader* Material::GetVertexShader() {
		return m_vertexShader;
	}

	PixelShader* Material::GetPixelShader() {
		return m_pixelShader;
	}

	bool Material::IsConstantBufferLoaded() {
		return m_constBuffer.IsLoaded();
	}

	void Material::CreateConstantBuffer(ID3D11Device* device) {
		m_constBuffer.Create(device);
	}

	void Material::BindConstantBuffer(ID3D11DeviceContext* context) {
		m_constBuffer.Bind(context);
	}

	void Material::UpdateConstantBufferData(DirectX::XMFLOAT4X4 world) {
		m_constBuffer.UpdateData(world);
	}

	void Material::UpdateConstantBuffer(ID3D11DeviceContext* context) {
		m_constBuffer.Update(context);
	}
}