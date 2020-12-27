#include "../include/GameObject.h"

namespace Venture {
	GameObject::GameObject() : 
		m_uniqueID(GetUniqueID()), m_handleIndex(GetNewHandleIndex(this)), m_components(std::list<Component*>()) {}

	GameObject::~GameObject() {
		Destroy();
	}

	void GameObject::AddComponent(Component* component) {
		m_components.push_back(component);
	}

	void GameObject::Update() {
		for (Component* c : m_components) {
			c->Update();
		}
	}
	void GameObject::EarlyUpdate() {
		for (Component* c : m_components) {
			c->EarlyUpdate();
		}
	}
	void GameObject::LateUpdate() {
		for (Component* c : m_components) {
			c->LateUpdate();
		}
	}
	GameObject** GameObject::GetAllGameObjects() {
		return gameObjectTable;
	}
	int GameObject::GetMaxGameObjects() {
		return MAX_GAME_OBJECTS;
	}
	GameObjectHandle GameObject::Create() {
		return GameObjectHandle(*(new GameObject()));
	}
	void GameObject::Destroy() {
		for (Component* c : m_components) {
			delete c;
		}
		FreeHandleIndex(m_handleIndex);
	}

	GameObjectHandle::GameObjectHandle(GameObject& object) :
		m_uniqueID(object.m_uniqueID),
		m_handleIndex(object.m_handleIndex) {
	}
	GameObject* GameObjectHandle::GetObject() {
		GameObject* object = gameObjectTable[m_handleIndex];
		if (object != nullptr && object->m_uniqueID == m_uniqueID) {
			return object;
		}
		return nullptr;
	}
}