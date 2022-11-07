#pragma once
#include <vector>
class MyGE
{
public:

	MyGE();

	int run();

	void ProcessInput();

protected:
	class RenderWindow* mWindow{nullptr};

	//Lua scripting
	class ScriptingManager* mScriptingManager;
	//Scene manager
	class SceneManager* mSceneManager;

	class ShaderManager* mShaderManager;
};

class SceneManager {
public:
	SceneManager() {

	};

	class Scene* GetNextScene(int dir) {
		if (mActiveSceneIndex + dir >= mScenes.size()) {
			mActiveSceneIndex = 0;
		}
		else if(mActiveSceneIndex + dir <= 0) {
			mActiveSceneIndex = mScenes.size() - 1;
		}
		else {
			mActiveSceneIndex += dir;
		}
		return mScenes[mActiveSceneIndex];
	};

	Scene* GetScene() {
		return mScenes[mActiveSceneIndex];
	}

	void AddScene(Scene& scene) {
		mScenes.push_back(&scene);
	}
private:
	std::vector<Scene*> mScenes;
	int mActiveSceneIndex = 0;
};