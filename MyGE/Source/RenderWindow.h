#pragma once
#include "MainWindow.h"
class RenderWindow : public MainWindow
{
public:
	RenderWindow();
	virtual void Init(struct GLFWwindow* window) override;
	void Render(float deltaTime);

	void SetScene(class Scene* scene) {
		mActiveScene = scene;
	}
private:
	class Scene* mActiveScene;

	float mScreenWidth = 1200;
	float mScreenHeight = 800;
	
};

