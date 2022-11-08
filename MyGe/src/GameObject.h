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
	GameObject(int ID) {
		mID = ID;
	};
	GameObject(GameObject* parent) : mParent(parent) {};


	virtual void Init() {
		for (int i = 0; i < mComponents.size(); i++) {
			mComponents[i]->Init();
		}
	};

	virtual void OnUpdate() {
		std::cout << "GameObject : OnUpdate" << std::endl;
		for (int i = 0; i < mComponents.size(); i++) {
			mComponents[i]->OnUpdate(0.1f);
		}
	};
	
	void AddComponent(Component* comp) { mComponents.push_back(comp); };

	template<typename T>
	T* GetComponent(GameObject object) {
		for (int i = 0; i < mComponents.size(); i++)
		{
			
		}
		return nullptr;
	}

	void SetID(int id) {
		mID = id;
	}
	int GetID() { return mID; };
	TransformComponent* GetTransform() { return GetComponent<TransformComponent>(this); };
protected:
	GameObject* mParent;
	
	std::vector<Component*> mComponents;

	int mID;
};

