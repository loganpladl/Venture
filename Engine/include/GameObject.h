#pragma once

#include <list>
#include "../include/Component.h"

namespace Venture {
	class GameObject {
	private:
		std::list<Component> components;
	public:
		void AddComponent(Component component) {
			components.push_back(component);
		}
	};
}