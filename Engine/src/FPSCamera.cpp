#include "../include/FPSCamera.h"
#include "../include/GameObject.h"
#include "../include/Input.h"
#include "../include/Time.h"
#include "../include/RenderManager.h"
#include "../include/Log.h"

// Need to include namespace for operator overloading
using namespace DirectX;

namespace Venture {
	FPSCamera::FPSCamera(GameObject* parent) : Camera(parent),
		m_position(0,0,0), m_direction(0,0,1), m_up(0,1,0), m_pitch(0), m_yaw(90), 
		m_moveSpeed(5), m_lookSpeed(5),
		m_mouseDeltaEventHandler(*this){
		EventSystem::RegisterHandler(&m_mouseDeltaEventHandler, EventType::MouseDelta);
	}

	void FPSCamera::Update() {
		// Update direction changes accrued by event handler
		UpdateDirection();

		

		XMVECTOR dir = XMLoadFloat3(&m_direction);
		XMVECTOR up = XMLoadFloat3(&m_up);
		XMVECTOR pos = XMLoadFloat3(&m_position);

		if (Keyboard::IsButtonPressed(Keyboard::KeyCode::W)) {
			pos += dir * m_moveSpeed * static_cast<float>(Time::DeltaTime());
		}
		if (Keyboard::IsButtonPressed(Keyboard::KeyCode::A)) {
			pos -= XMVector3Normalize(XMVector3Cross(up, dir)) * m_moveSpeed * static_cast<float>(Time::DeltaTime());
		}
		if (Keyboard::IsButtonPressed(Keyboard::KeyCode::S)) {
			pos -= dir * m_moveSpeed * static_cast<float>(Time::DeltaTime());
		}
		if (Keyboard::IsButtonPressed(Keyboard::KeyCode::D)) {
			pos += XMVector3Normalize(XMVector3Cross(up, dir)) * m_moveSpeed * static_cast<float>(Time::DeltaTime());
		}
		XMStoreFloat3(&m_position, pos);

		RenderManager::UpdateViewTransform(GetViewTransform());
	}

	void FPSCamera::UpdateDirection() {
		float yawRadians = DirectX::XMConvertToRadians(m_yaw);
		float pitchRadians = DirectX::XMConvertToRadians(m_pitch);
		m_direction.x = static_cast<float>(cos(yawRadians) * cos(pitchRadians));
		m_direction.y = static_cast<float>(sin(pitchRadians));
		m_direction.z = static_cast<float>(sin(yawRadians) * cos(pitchRadians));

		DirectX::XMVECTOR vec = DirectX::XMLoadFloat3(&m_direction);
		vec = DirectX::XMVector3Normalize(vec);
		DirectX::XMStoreFloat3(&m_direction, vec);
	}

	// Returns left handed look at matrix
	DirectX::XMFLOAT4X4 FPSCamera::GetViewTransform() {
		DirectX::XMVECTOR eyePos = DirectX::XMLoadFloat3(&m_position);
		DirectX::XMVECTOR eyeDir = DirectX::XMLoadFloat3(&m_direction);
		DirectX::XMMATRIX transform = DirectX::XMMatrixLookToLH(eyePos, eyeDir, { 0, 1, 0 });
		
		DirectX::XMFLOAT4X4 result;
		DirectX::XMStoreFloat4x4(&result, transform);
		return result;
	}

	void FPSCamera::MouseDeltaEventHandler::Handle(Event* event) {
		MouseDeltaEvent* mouseDeltaEvent = dynamic_cast<MouseDeltaEvent*>(event);
		std::pair<int, int> pos = mouseDeltaEvent->GetPosition();
		m_camera.m_yaw += -pos.first * m_camera.m_lookSpeed * static_cast<float>(Time::DeltaTime());
		m_camera.m_pitch += -pos.second * m_camera.m_lookSpeed * static_cast<float>(Time::DeltaTime());

		if (m_camera.m_pitch > 89) {
			m_camera.m_pitch = 89;
		}
		if (m_camera.m_pitch < -89) {
			m_camera.m_pitch = -89;
		}
	}

}