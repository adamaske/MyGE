#pragma once
#include "MyGEMode.h"
class MyGEEditor : public MyGEMode {
public:
	//Called when we start the editor
	virtual void Init() override;
	//We still want to render and stuff, we dont
	virtual void OnUpdate(float deltaTime) override;

	bool LoadScene(std::string fileName);

	void StartPlay();
	void StopPlay();
	std::shared_ptr<class Scene> GetScene();
private:
	std::shared_ptr<Scene> mEditorScene;
};
