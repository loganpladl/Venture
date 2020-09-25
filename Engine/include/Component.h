#pragma once

#include "Event.h"

namespace Venture {
	enum ComponentType {
		Transform,
		MeshInstance
	};
	class Component {
	protected:
		ComponentType m_type;
		Component(ComponentType type) : m_type(type) {}
	public:
		virtual void Update() = 0;
		inline ComponentType GetType() { return m_type; }
		inline bool IsType(ComponentType type) { return type == m_type; }
		virtual void ReceiveEvents(Event event);
	};
}