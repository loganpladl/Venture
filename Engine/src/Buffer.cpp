#include "../include/Buffer.h"
#include <stdlib.h>
#include <cstring>

namespace Venture {
	Buffer::Buffer(size_t bytes) {
		m_buffer = new char[bytes];
		m_bytes = bytes;
	}
	Buffer::Buffer() {
		m_buffer = nullptr;
		m_bytes = 0;
	}
	Buffer::~Buffer() {
		delete m_buffer;
	}

	Buffer::Buffer(const Buffer& buffer) {
		m_bytes = buffer.GetBytes();
		m_buffer = new char[m_bytes];
		memcpy(m_buffer, buffer.GetBuffer(), m_bytes);
	}

	Buffer& Buffer::operator=(const Buffer& buffer) {
		m_bytes = buffer.GetBytes();
		m_buffer = new char[m_bytes];
		memcpy(m_buffer, buffer.GetBuffer(), m_bytes);
		return *this;
	}

	void Buffer::Create(size_t bytes) {
		if (m_buffer != nullptr) {
			delete m_buffer;
		}
		m_buffer = new char[bytes];
		m_bytes = bytes;
	}

	char* Buffer::GetBuffer() const {
		return m_buffer;
	}

	size_t Buffer::GetBytes() const {
		return m_bytes;
	}
}