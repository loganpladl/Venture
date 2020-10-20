#pragma once

namespace Venture {
	class Buffer {
	private:
		char* m_buffer;
		size_t m_bytes;
	public:
		Buffer(size_t bytes);
		Buffer();
		~Buffer();

		// Delete copy constructor and assignment operator to avoid passing by value
		Buffer(const Buffer&) = delete;
		Buffer& operator=(const Buffer&) = delete;

		void Create(size_t bytes);
		char* GetBuffer();
		size_t GetBytes();
	};
}