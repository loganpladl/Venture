#include "../include/Shader.h"
#include "../include/FileSystem.h"

namespace Venture {
	Shader::Shader(ShaderType type, std::string path) : m_type(type), m_path(path) {
	}

	void Shader::ReadFile() {
		File::AsyncOpenReadCloseRequest* request = FileSystem::AsyncOpenReadCloseFile(m_path.c_str(), "rb");
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