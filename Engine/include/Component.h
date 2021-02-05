#pragma once

#include "Event.h"

namespace Venture {
	// Forward declaration
	class GameObject;

	enum class ComponentType {
		Transform,
		MeshInstance,
		Camera
	};
	class Component {
	protected:
		ComponentType m_type;
		GameObject* m_parentObject;
		Component(ComponentType type, GameObject* parent) : m_type(type), m_parentObject(parent) {}
	public:
		virtual void Update() {};
		virtual void EarlyUpdate() {};
		virtual void LateUpdate() {};
		inline ComponentType GetType() { return m_type; }
		inline bool IsType(ComponentType type) { return type == m_type; }
		virtual void ReceiveEvents(Event event) {};
		inline GameObject* GetGameObject() {
			return m_parentObject;
		}
	};
}