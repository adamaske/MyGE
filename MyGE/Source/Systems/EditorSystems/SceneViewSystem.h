#pragma once
#include "../System.h"
class SceneViewSystem : public System {
public:
	SceneViewSystem();
	virtual void Init();
	virtual void OnUpdate(float deltaTime);

private:
};