#pragma once
//#include "glew.h"
#include <vector>
#include "ScriptingManager.h"
#include "ShaderManager.h"
#include "RenderWindow.h"
class SceneManager {
public:
	SceneManager() {

	};

	class Scene& GetNextScene(int dir) {
		if (mActiveSceneIndex + dir >= mScenes.size()) {
			mActiveSceneIndex = 0;
		}
		else if (mActiveSceneIndex + dir <= 0) {
			mActiveSceneIndex = mScenes.size() - 1;
		}
		else {
			mActiveSceneIndex += dir;
		}
		return *mScenes[mActiveSceneIndex];
	};

	Scene& GetScene() {
		return *mScenes[mActiveSceneIndex];
	}

	void AddScene(Scene& scene) {
		mScenes.push_back(&scene);
	}
private:
	std::vector<Scene*> mScenes;
	int mActiveSceneIndex = 0;
};
class MyGE
{
public:

	MyGE();

	int run();

	void ProcessInput();


protected:
	RenderWindow* mWindow;

	////Lua scripting
	ScriptingManager* mScriptingManager;
	//Scene manager
	SceneManager* mSceneManager;

	ShaderManager* mShaderManager;

	Scene* mScene;

	GLFWwindow* mRenderWindow;
};

