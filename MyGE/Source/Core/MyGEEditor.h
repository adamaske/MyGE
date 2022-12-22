#pragma once
#include "MyGEMode.h"
class MyGEEditor : public MyGEMode {
public:
	//Called when we start the editor
	virtual void Init() override;
	//We still want to render and stuff, we dont
	virtual void OnUpdate(float deltaTime) override;

	bool LoadScene(std::string fileName);
	bool LoadScene(std::shared_ptr<Scene> scene);

	void StartPlay();
	void StopPlay();
	std::shared_ptr<class Scene> GetScene();
private:
	
	std::shared_ptr<Scene> mEditorScene;
	std::unordered_map<const char*, class System*> mSystems;

	bool bEditorRunning = true;


	//The scene viewport, where we see the scene
	std::shared_ptr<class RenderWindow> mSceneViewport;
	//The window where the game view (main camera) is seen
	std::shared_ptr<class RenderWindow> mGameRenderViewport;
	//Should we create another window, or use the same one as the editor uses for scene view
	bool bPopoutRuntime = false;
};
