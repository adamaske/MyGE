#pragma once
#include "MainWindow.h"
class RenderWindow 
{
public:
	RenderWindow(GLFWwindow* window) : mWindow(window) {

	};
	void Init();


	GLFWwindow* GetWindow() { return mWindow; };

	void Render();

	void Close();

	bool ShouldClose();
private:
	class Scene* mActiveScene;
	GLFWwindow* mWindow;
	
};

