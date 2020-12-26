#pragma once

#include "Shader.h"
#include <d3d11.h>

namespace Venture {
	class VertexShader : public Shader {
	public:
		VertexShader(std::string path, ID3D11Device* device, ID3D11DeviceContext* context);
		void Bind() override;
		~VertexShader();
	private:
		ID3D11VertexShader* m_vertexShader;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
	};
}