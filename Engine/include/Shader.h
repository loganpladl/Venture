#pragma once
#include <string>
#include "Buffer.h"

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
		// Virtual function to bind shader to hardware pipeline
		virtual void Bind() = 0;
		ShaderType m_type;
		virtual ~Shader() {}

		Buffer m_bytecode;
	public:
		void* GetBytecode();
		size_t GetBytecodeSize();
	};
}