#pragma once

#include "Camera.h"
#include <DirectXMath.h>
#include "EventHandler.h"
#include "Event.h"

// TODO: Probably should use transform of parent object instead of separate 
// member variable positions/orientation here.

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
		float m_moveSpeed;
		float m_lookSpeed;

		class MouseDeltaEventHandler : public EventHandler {
		private:
			FPSCamera& m_camera;
		public:
			MouseDeltaEventHandler(FPSCamera& camera) : m_camera(camera) {}
			void Handle(Event* event) override;
		};
	public:
		MouseDeltaEventHandler m_mouseDeltaEventHandler;
	};
}