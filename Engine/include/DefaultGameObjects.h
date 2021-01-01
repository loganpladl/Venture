#pragma once
#include "GameObject.h"

namespace Venture {
	class DefaultGameObjects {
	private:
	public:
		static GameObjectHandle GetNewCube();
		static GameObjectHandle GetNewFPSCamera();
	};
}