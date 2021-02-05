#pragma once
#include "Vertex.h"
#include <vector>
#include <d3d11.h>
#include<DirectXMath.h>

namespace Venture {
	class Mesh {
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<int> indices);
		Mesh();
		// Create vertex/index buffers from CPU vertex/index data
		void CreateBuffers(ID3D11Device* device);
		// Returns true if mesh is loaded in GPU (buffers are not nullptrs)
		bool IsLoaded();
		// Bind buffers to D3D11 pipeline
		void BindBuffers(ID3D11DeviceContext* context);
		// Explicitly unload buffers from GPU
		void DestroyBuffers();
		// Also release buffers in destructor if they are still loaded
		~Mesh();
		int NumVertices();
		int NumIndices();
	private:
		std::vector<Vertex> m_vertices;
		std::vector<int> m_indices;
		ID3D11Buffer* m_vertexBuffer;
		ID3D11Buffer* m_indexBuffer;
	};
}