#include "../include/Camera.h"
#include "../include/GameObject.h"

namespace Venture {
	Camera::Camera(GameObject* parent) : Component(ComponentType::Camera, parent) {

	}
}