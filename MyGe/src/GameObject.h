#pragma once
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Components.h"
#include <vector>
#include <iostream>
#include <unordered_map>
class GameObject
{
public:
	GameObject() {};
	GameObject(GameObject* parent) : mParent(parent) {};

	virtual void Init() {
		for (int i = 0; i < mComponents.size(); i++) {
			mComponents[i]->Init();
		}
	};

	virtual void OnUpdate() {
		for (int i = 0; i < mComponents.size(); i++) {
			mComponents[i]->OnUpdate(0.1f);
		}
	};
	
	void AddComponent(Component* comp) { mComponents.push_back(comp); };

	template<typename T>
	T* GetComponent(GameObject object) {
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (dynamic_cast<T>(mComponents[i])) {
				return dynamic_cast<T>(mComponents[i]);
			}
		}
		return nullptr;
	}
protected:
	GameObject* mParent;
	
	std::vector<Component*> mComponents;
};

class Cube : public GameObject {
public:
	Cube();
	Cube(GameObject* parent) : GameObject(parent) {};
};