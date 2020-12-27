#pragma once
#include "Component.h"
#include "Mesh.h"

namespace Venture {
	class MeshInstance : public Component {
	public:
		MeshInstance(Mesh* mesh) : Component(ComponentType::MeshInstance), m_mesh(mesh) {

		}
	private:
		Mesh* m_mesh;
	};
}