#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "MyGE.h"
class Scene
{
public:
	Scene(){
		std::cout << "Scene created!" << std::endl;
	};

	virtual void Init();

	virtual void OnUpdate(float deltaTime);

	void AddScene(Scene* scene) {

	}

	void ViewportRezised(int width, int height);
private:

	std::unordered_map<const char*, GameObject> mGameObjects;
	std::unordered_map<const char*, class System*> mSystems;

	class Registry* mRegistry;

	CameraComponent* mSceneCamera;

	int mViewportWidth = 0;
	int mViewportHeight = 0;

};
