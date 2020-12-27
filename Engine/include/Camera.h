#pragma once
#include "Component.h"
#include <DirectXMath.h>

namespace Venture {
	// Forward declaration
	class GameObject;

	class Camera : public Component {
	protected:
		Camera(GameObject* parent);
	public:
		virtual DirectX::XMFLOAT4X4 GetViewTransform() = 0;
	};
}