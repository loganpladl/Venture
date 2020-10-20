#include "../include/Buffer.h"
#include <stdlib.h>

namespace Venture {
	Buffer::Buffer(size_t bytes) {
		m_buffer = new char[bytes];
		m_bytes = bytes;
	}
	Buffer::Buffer() {
		m_buffer = NULL;
		m_bytes = 0;
	}
	Buffer::~Buffer() {
		delete m_buffer;
	}

	void Buffer::Create(size_t bytes) {
		if (m_buffer != NULL) {
			delete m_buffer;
		}
		m_buffer = new char[bytes];
		m_bytes = bytes;
	}

	char* Buffer::GetBuffer() {
		return m_buffer;
	}

	size_t Buffer::GetBytes() {
		return m_bytes;
	}
}