#pragma once
#include "MainWindow.h"
class RenderWindow : public MainWindow
{
public:
	RenderWindow();
	virtual void Init(struct GLFWwindow* window) override;
	void Render();

	void SetActiveScene(class Scene* scene);
	Scene* GetActiveScene();
private:
	class Scene* mActiveScene;

	
};

