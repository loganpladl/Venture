#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"

namespace Venture {
	class MeshInstance : public Component {
	public:
		MeshInstance(GameObject* parent, Mesh* mesh, Material* material) : Component(ComponentType::MeshInstance, parent), m_mesh(mesh), m_material(material) {

		}
		void Update() override;
	private:
		Mesh* m_mesh;
		Material* m_material;
	};
}