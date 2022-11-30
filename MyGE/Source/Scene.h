#pragma once
#include "pch.h"

using GameObject = uint32_t;
class Scene
{
public:
	Scene();

	virtual void Init();

	virtual void OnUpdate(float deltaTime);

	void AddScene(Scene* scene) {

	}

	void ViewportRezised(int width, int height);
private:

	std::unordered_map<const char*, GameObject> mGameObjects;
	std::unordered_map<const char*, class System*> mSystems;

	class Registry* mRegistry;

	struct CameraComponent* mSceneCamera;

	int mViewportWidth = 0;
	int mViewportHeight = 0;

};
