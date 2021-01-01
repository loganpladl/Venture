#pragma once
#include "Component.h"
#include "Mesh.h"

namespace Venture {
	class MeshInstance : public Component {
	public:
		MeshInstance(GameObject* parent, Mesh* mesh) : Component(ComponentType::MeshInstance, parent), m_mesh(mesh) {

		}
	private:
		Mesh* m_mesh;
	};
}