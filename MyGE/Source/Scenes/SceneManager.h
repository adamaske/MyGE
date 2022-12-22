#pragma once
#include "Scene.h"
#include <unordered_map>
#include <memory>
class SceneManager {
public:
	SceneManager();
	
	//Once resources loading and stuff happends, this should be full of scene information
	std::shared_ptr<Scene> GetScene(const char* sceneName);
		
	
private:
	//Should it be a vector instead? 
	std::unordered_map<const char*, std::shared_ptr<Scene>> mScenes;
};