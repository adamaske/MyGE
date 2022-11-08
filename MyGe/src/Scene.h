#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Components.h"
#include "GameObject.h"
#include "ShaderManager.h"
#include "Registry.h"
class Scene
{
public:
	Scene() {
		std::cout << "Scene created!" << std::endl;
	};

	virtual void Init(class ShaderManager* shaderManager);

	virtual void OnUpdate();

	void MoveForward() {
		TransformComponent* t = mObjects["Camera"]->GetComponent<TransformComponent>(mObjects["Camera"]);
		if (t) {
			t->AddLocalOffset(glm::vec3(0, 1, 0));
		}
	}
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
	Shader* GetActiveSceneShader() { return &mShaderManager->GetShader("PlainShader"); };
	std::vector<class RenderComponent*> GetRenders() { return mRenders; };
private:
	std::vector<Component*> mComponents;
	Shader* shader;
	CameraComponent* mActiveCamera;

	std::unordered_map <std::string, GameObject*> mObjects;
	std::vector<RenderComponent*> mRenders;
	//The scene wants to know of all the shaders
	ShaderManager* mShaderManager;
};

