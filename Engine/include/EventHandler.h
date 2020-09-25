#pragma once
#include "Event.h"

namespace Venture {
	class EventHandler {
	public:
		virtual ~EventHandler() {}
		virtual void Handle(Event* event) = 0;
	};
}