#pragma once
#include <iostream>
#include <vector>
#include "Components.h"
#include "GameObject.h"
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

		for (int i = 0; i < mObjects.size(); i++)
		{
			if ((mObjects[i]->GetComponent<T>(mObjects[i])) != nullptr) {
				arr.push_back( mObjects[i]->GetComponent<T>(mObjects[i]));
			}
			
		}

		return arr;
	}

	CameraComponent* GetActiveCamera() { return mActiveCamera; };
	//Temporary
	Shader* GetActiveSceneShader() { return shader; };
	std::vector<class RenderComponent*> GetRenders() { return mRenders; };
private:
	std::vector<Component*> mComponents;
	Shader* shader;
	CameraComponent* mActiveCamera;

	std::vector<class GameObject*> mObjects;
	std::vector<RenderComponent*> mRenders;
};

