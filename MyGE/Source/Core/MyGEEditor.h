#pragma once
#include "MyGEMode.h"
#include <unordered_map>
#include <memory>
#include <string>
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

	void ViewportRezised(int width, int height);


private:
	
	std::shared_ptr<Scene> mEditorScene;
	std::unordered_map<const char*, std::shared_ptr<class System>> mEditorSystems;

	bool bEditorRunning = true;

	//What scene do we want to start up with
	//Should we do all this in an editor system instead?
	//for example SceneViewSystem, renders with MyGEEditor.mEditorCamera 
	//GameViewSystem, gameview renders with the bMainCamera camera
	std::shared_ptr<class EditorCamera> mEditorCamera;
	//The window where the game view (main camera) is seen
	std::shared_ptr<class RenderWindow> mSceneViewport;
	//The window where the game view (main camera) is seen
	std::shared_ptr<RenderWindow> mGameViewport;
	//Should we create another window, or use the same one as the editor uses for scene view
	bool bPopoutRuntime = false;
};
