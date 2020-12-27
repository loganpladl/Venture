#pragma once

#include <list>
#include "../include/Component.h"

namespace Venture {
	// Forward declarations
	class GameObject;
	class GameObjectHandle;
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
		GameObject();
		~GameObject();

		void AddComponent(Component* component);

		void Update();

		void EarlyUpdate();

		void LateUpdate();

		static GameObject** GetAllGameObjects();

		static int GetMaxGameObjects();

		static GameObjectHandle Create();

		void Destroy();
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
		explicit GameObjectHandle(GameObject& object);
		GameObject* GetObject();
	};
}