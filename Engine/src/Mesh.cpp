#include "../include/Mesh.h"

namespace Venture {
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices) :
		m_vertices(vertices), m_indices(indices), m_vertexBuffer(nullptr), m_indexBuffer(nullptr){}

	void Mesh::CreateBuffers(ID3D11Device* device) {
		// Create vertex buffer
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.CPUAccessFlags = 0u;
		bufferDesc.MiscFlags = 0u;
		bufferDesc.ByteWidth = m_vertices.size() * sizeof(Vertex);
		bufferDesc.StructureByteStride = sizeof(Vertex);
		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = m_vertices.data();
		device->CreateBuffer(&bufferDesc, &subData, &m_vertexBuffer);

		// Create index buffer
		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.CPUAccessFlags = 0u;
		indexBufferDesc.MiscFlags = 0u;
		indexBufferDesc.ByteWidth = m_indices.size()*sizeof(int);
		indexBufferDesc.StructureByteStride = sizeof(int);
		D3D11_SUBRESOURCE_DATA indexSubData = {};
		indexSubData.pSysMem = m_indices.data();
		device->CreateBuffer(&indexBufferDesc, &indexSubData, &m_indexBuffer);
	}

	bool Mesh::IsLoaded() {
		return m_vertexBuffer != nullptr && m_indexBuffer != nullptr;
	}

	void Mesh::BindBuffers(ID3D11DeviceContext* context) {
		// Bind vertex buffer
		const UINT stride = sizeof(Vertex);
		const UINT offset = 0;
		context->IASetVertexBuffers(0u, 1u, &m_vertexBuffer, &stride, &offset);

		// Bind index buffer
		context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	void Mesh::DestroyBuffers() {
		if (m_vertexBuffer != nullptr)
			m_vertexBuffer->Release();
		if (m_indexBuffer != nullptr)
			m_indexBuffer->Release();
	}

	Mesh::~Mesh() {
		DestroyBuffers();
	}

	int Mesh::NumVertices() {
		return m_vertices.size();
	}

	int Mesh::NumIndices() {
		return m_indices.size();
	}
}