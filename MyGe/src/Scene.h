#pragma once
#include <iostream>
#include <vector>

class Scene
{
public:
	Scene() {
		
	};

	virtual void Init();

	//virtual void OnUpdate();
};

class TwoCubesScene : public Scene{
public:
	TwoCubesScene() : Scene(){};

	//virtual void Init() override;

	//virtual void OnUpdate() override;
}

