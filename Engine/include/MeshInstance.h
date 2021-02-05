#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include "DirectXMath.h"

namespace Venture {
	class MeshInstance : public Component {
	public:
		MeshInstance(GameObject* parent, Mesh* mesh, Material* material) : Component(ComponentType::MeshInstance, parent), m_mesh(mesh), m_material(material),
			m_worldTransform(
				{ 1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1 }) {

		}
		void Update() override;
	private:
		Mesh* m_mesh;
		Material* m_material;
		DirectX::XMFLOAT4X4 m_worldTransform;
	};
}