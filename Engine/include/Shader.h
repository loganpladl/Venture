#pragma once
#include <string>
#include "Buffer.h"
#include <d3d11.h>

namespace Venture {
	enum class ShaderType {
		Vertex,
		Geometry,
		Pixel
	};

	// Handles file IO for shaders, derived classes handle hardware pipeline
	class Shader {
	protected:
		Shader(ShaderType type, std::string path);
		// Virtual function to create and bind shaders in hardware pipeline
		virtual void Create(ID3D11Device* device) = 0;
		virtual void Bind(ID3D11DeviceContext* context) = 0;
		// Returns true if shader exists on GPU
		virtual bool IsLoaded() = 0;
		ShaderType m_type;
		virtual ~Shader() {}
		Buffer m_bytecode;
		std::string m_path;
	public:
		void ReadFile();
		void* GetBytecode();
		size_t GetBytecodeSize();
	};
}