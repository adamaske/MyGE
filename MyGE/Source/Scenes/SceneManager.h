#pragma once
#include "Scene.h"
class SceneManager {
public:
	SceneManager();


	
private:
	std::unordered_map<const char*, std::shared_ptr<Scene>> mScenes;
};