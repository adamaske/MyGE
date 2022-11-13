#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "MyGE.h"
class Scene
{
public:
	Scene(class ShaderManager& shader) : mShaderManager(shader) {
		std::cout << "Scene created!" << std::endl;
	};

	virtual void Init();

	virtual void OnUpdate(float deltaTime);

	void AddScene(Scene* scene) {

	}

	void ViewportRezised(int width, int height);
private:
	//The scene wants to know of all the shaders
	ShaderManager& mShaderManager;

	std::unordered_map<const char*, class System*> mSystems;

	CameraComponent* mSceneCamera;

	int mViewportWidth = 0;
	int mViewportHeight = 0;

};
