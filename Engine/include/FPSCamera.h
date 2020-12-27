#pragma once

#include "Camera.h"
#include <DirectXMath.h>

namespace Venture {
	class FPSCamera : public Camera {
	public:
		FPSCamera(GameObject* parent);
		DirectX::XMFLOAT4X4 GetViewTransform() override;
		void Update() override;
	private:
		void UpdateDirection();
		DirectX::XMFLOAT3 m_position;
		DirectX::XMFLOAT3 m_direction;
		DirectX::XMFLOAT3 m_up;
		float m_pitch;
		float m_yaw;
		float m_speed;
	};
}