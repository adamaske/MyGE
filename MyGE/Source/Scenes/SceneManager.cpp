#include "pch.h"
#include "SceneManager.h"

#include "Scene.h"

SceneManager::SceneManager() {
	//Create scenes
}

std::shared_ptr<Scene> SceneManager::GetScene(const char* sceneName)
{
	// TODO: insert return statement here
	if (mScenes.find(sceneName) != mScenes.end()) {
		//There is a scene here
		return mScenes[sceneName];
	}
}
