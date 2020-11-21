#pragma once
#include "Component.h"

namespace Venture {
	class MeshInstance : public Component {
	public:
		MeshInstance() : Component(ComponentType::MeshInstance) {}
	};
}