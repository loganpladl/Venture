#pragma once

#include "Component.h"
#include <DirectXMath.h>

namespace Venture {
	class Transform : public Component {
	public:
		Transform(GameObject* parent) : Component(ComponentType::Transform, parent),
			m_position(0,0,0), m_rotation(1,0,0,0), m_scale(1,1,1) {
		}
		Transform(GameObject* parent, DirectX::XMFLOAT3 position) : Component(ComponentType::Transform, parent),
			m_position(position), m_rotation(1, 0, 0, 0), m_scale(1, 1, 1) {
		}
		void Update() {}
		void EarlyUpdate() {}
		void LateUpdate() {}
		DirectX::XMFLOAT3 GetPos() { return m_position; }
		DirectX::XMFLOAT4 GetRot() { return m_rotation; }
		DirectX::XMFLOAT3 GetScale() { return m_scale; }
		// Object space to World space matrix transformation
		DirectX::XMFLOAT4X4 ObjectToWorld() {
			// Load vectors into SIMD XMVECTORs
			DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&m_position);
			DirectX::XMVECTOR rot = DirectX::XMLoadFloat4(&m_rotation);
			DirectX::XMVECTOR scale = DirectX::XMLoadFloat3(&m_scale);
			// Compute affine transformation matrix
			DirectX::XMMATRIX affineTransform = DirectX::XMMatrixAffineTransformation(scale, rot, { 0, 0, 0 }, pos);
			// Return result as XMFLOAT4X4
			DirectX::XMFLOAT4X4 result;
			DirectX::XMStoreFloat4x4(&result, affineTransform);
			return result;
		}
	private:
		DirectX::XMFLOAT3 m_position;
		// Quaternion orientation
		DirectX::XMFLOAT4 m_rotation;
		DirectX::XMFLOAT3 m_scale;
	};
}