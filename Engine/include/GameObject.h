#pragma once

#include <list>
#include "../include/Component.h"

namespace Venture {
	// Forward declarations
	class GameObject;
	static int GetUniqueID();
	static int GetNewHandleIndex(GameObject* gameObject);
	static void FreeHandleIndex(int index);

	static const int MAX_GAME_OBJECTS = 2048;
	static GameObject* gameObjectTable[MAX_GAME_OBJECTS] = { nullptr };

	class GameObject {
	private:
		int m_uniqueID;
		int m_handleIndex;
		std::list<Component*> m_components;
		friend class GameObjectHandle;
	public:
		GameObject() : m_uniqueID(GetUniqueID()), m_handleIndex(GetNewHandleIndex(this)) {
			m_components = std::list<Component*>();
		}
		~GameObject() {
			for (Component* c : m_components) {
				delete c;
			}
			FreeHandleIndex(m_handleIndex);
		}
		void AddComponent(Component* component) {
			m_components.push_back(component);
		}
		void Update() {
			for (Component* c : m_components) {
				c->Update();
			}
		}
		void EarlyUpdate() {
			for (Component* c : m_components) {
				c->EarlyUpdate();
			}
		}
		void LateUpdate() {
			for (Component* c : m_components) {
				c->LateUpdate();
			}
		}
		static GameObject** GetAllGameObjects() {
			return gameObjectTable;
		}
		static int GetMaxGameObjects() {
			return MAX_GAME_OBJECTS;
		}
	};

	static int nextUniqueID = 0;
	static int GetUniqueID() {
		int ID = nextUniqueID;
		++nextUniqueID;
		return ID;
	}
	
	// Return new handle and set corresponding element in game object table
	static int GetNewHandleIndex(GameObject* gameObject) {
		for (int i = 0; i < MAX_GAME_OBJECTS; i++) {
			if (gameObjectTable[i] == nullptr) {
				gameObjectTable[i] = gameObject;
				return i;
			}
		}
		// Couldn't find empty slot
		return -1;
	}

	static void FreeHandleIndex(int index) {
		gameObjectTable[index] = nullptr;
	}

	class GameObjectHandle {
	private:
		int m_uniqueID;
		int m_handleIndex;
	public:
		explicit GameObjectHandle(GameObject& object) :
			m_uniqueID(object.m_uniqueID),
			m_handleIndex(object.m_handleIndex) {
		}
		GameObject* GetObject() {
			GameObject* object = gameObjectTable[m_handleIndex];
			if (object != nullptr && object->m_uniqueID == m_uniqueID) {
				return object;
			}
			return nullptr;
		}
	};

	
}