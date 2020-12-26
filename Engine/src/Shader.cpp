#include "../include/Shader.h"
#include "../include/FileSystem.h"

namespace Venture {
	Shader::Shader(ShaderType type, std::string path) : m_type(type) {
		File::AsyncOpenReadCloseRequest* request = FileSystem::AsyncOpenReadCloseFile(path.c_str(), "rb");
		request->Wait();
		m_bytecode = request->GetBuffer();
	}

	void* Shader::GetBytecode() {
		return m_bytecode.GetBuffer();
	}
	size_t Shader::GetBytecodeSize() {
		return m_bytecode.GetBytes();
	}
}