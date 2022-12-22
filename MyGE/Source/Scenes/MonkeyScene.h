#pragma once
#include "Scene.h"
class MonkeyScene : public Scene {
public:
	MonkeyScene();

	virtual void Init() override;
	
	virtual void OnUpdate(float deltaTime) override;
	
};