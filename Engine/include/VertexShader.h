#pragma once

#include "Shader.h"
#include <d3d11.h>

namespace Venture {
	class VertexShader : public Shader {
	public:
		VertexShader(std::string path);
		void Create(ID3D11Device* device) override;
		void Bind(ID3D11DeviceContext* context) override;
		bool IsLoaded() override;
		~VertexShader();
	private:
		ID3D11VertexShader* m_vertexShader;
	};
}