#pragma once

#include "Component.h"
#include <DirectXMath.h>

namespace Venture {
	class Transform : public Component {
	public:
		Transform() : Component(ComponentType::Transform),
			position(0,0,0), rotation(1,0,0,0), scale(1,1,1) {
		}
	private:
		DirectX::XMFLOAT3 position;
		// Quaternion orientation
		DirectX::XMFLOAT4 rotation;
		DirectX::XMFLOAT3 scale;
	};
}