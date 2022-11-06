#pragma once
#include "MainWindow.h"
class RenderWindow : public MainWindow
{
public:
	RenderWindow();
	virtual int Init(struct GLFWwindow* window) override;
	void PreRender();
	void Render();

	void SetActiveScene(class Scene* scene);
	Scene* GetActiveScene();
private:
	class Scene* mActiveScene;

	
};

