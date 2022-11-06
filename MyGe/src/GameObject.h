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
	GameObject();
	GameObject(GameObject* parent);

	std::vector<Component*> mComponents;
	void AddComponent(Component* comp) { mComponents.push_back(comp); };
	
	

};

