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

		// Deep copy
		Buffer(const Buffer&);
		Buffer& operator=(const Buffer&);

		void Create(size_t bytes);
		char* GetBuffer() const;
		size_t GetBytes() const;
		inline bool IsNull() const {
			return m_buffer == nullptr;
		}
	};
}