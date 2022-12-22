#pragma once

#include "../System.h"
class GameViewSystem : public System {
public:
	GameViewSystem();
	virtual void Init();
	virtual void OnUpdate(float deltaTime);

private:
	std::shared_ptr<class RenderWindow> mGameViewport;
};