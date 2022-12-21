#pragma once
#include "MyGEMode.h"
#include "../Scenes/Scene.h"
class MyGERuntime : public MyGEMode {
public:
	//MyGERuntime(Scene& scene), this will take in some binary format of a scene, for now a scene class
	MyGERuntime();

	//Called when we start the runtime, should call start functions on the items
	virtual void Init() override;
	virtual void OnUpdate(float deltaTime) override;

	void StartRuntime(std::shared_ptr<Scene> scene);
	void StopRuntime();
private:
	std::shared_ptr<Scene> mScene;

};