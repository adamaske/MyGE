#pragma once
#include <iostream>
#include <vector>
#include "Components.h"
class Scene
{
public:
	Scene() {
		std::cout << "Scene created!" << std::endl;
	};

	virtual void Init();

	virtual void OnUpdate();

	template<typename T>
	std::vector<T*> GetComponents() {
		std::vector<T*> arr;

		for (int i = 0; i < mComponents.size(); i++)
		{
			if (dynamic_cast<RenderComponent*>(mComponents[i])) {
				arr.push_back(dynamic_cast<RenderComponent*>(mComponents[i]));
			}
		}

		return arr;
	}

private:
	std::vector<Component*> mComponents;
};

