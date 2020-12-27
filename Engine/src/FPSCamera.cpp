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
		m_position(0,0,0), m_direction(0,0,1), m_up(0,1,0), m_pitch(0), m_yaw(0), m_speed(10) {

	}

	void FPSCamera::Update() {
		XMVECTOR dir = XMLoadFloat3(&m_direction);
		XMVECTOR up = XMLoadFloat3(&m_up);
		XMVECTOR pos = XMLoadFloat3(&m_position);

		if (Keyboard::IsButtonPressed(Keyboard::KeyCode::W)) {
			pos += dir * m_speed * static_cast<float>(Time::DeltaTime());
		}
		if (Keyboard::IsButtonPressed(Keyboard::KeyCode::A)) {
			pos -= XMVector3Normalize(XMVector3Cross(up, dir)) * m_speed * static_cast<float>(Time::DeltaTime());
		}
		if (Keyboard::IsButtonPressed(Keyboard::KeyCode::S)) {
			pos -= dir * m_speed * static_cast<float>(Time::DeltaTime());
		}
		if (Keyboard::IsButtonPressed(Keyboard::KeyCode::D)) {
			pos += XMVector3Normalize(XMVector3Cross(up, dir)) * m_speed * static_cast<float>(Time::DeltaTime());
		}
		XMStoreFloat3(&m_position, pos);

		RenderManager::UpdateViewTransform(GetViewTransform());
	}

	void FPSCamera::UpdateDirection() {
		float yawRadians = DirectX::XMConvertToRadians(m_yaw);
		float pitchRadians = DirectX::XMConvertToRadians(m_pitch);
		m_direction.x = cos(yawRadians) * cos(pitchRadians);
		m_direction.x = sin(pitchRadians);
		m_direction.z = sin(yawRadians) * cos(pitchRadians);

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


}