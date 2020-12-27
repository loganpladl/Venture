#pragma once

#include "Event.h"

namespace Venture {
	// Forward declaration
	class GameObject;

	enum ComponentType {
		Transform,
		MeshInstance
	};
	class Component {
	protected:
		ComponentType m_type;
		GameObject* m_parentObject;
		Component(ComponentType type, GameObject* parent) : m_type(type), m_parentObject(parent) {}
	public:
		virtual void Update() = 0;
		virtual void EarlyUpdate() = 0;
		virtual void LateUpdate() = 0;
		inline ComponentType GetType() { return m_type; }
		inline bool IsType(ComponentType type) { return type == m_type; }
		virtual void ReceiveEvents(Event event);
	};
}