#pragma once
#include "MainWindow.h"
class RenderWindow : public MainWindow
{
public:
	RenderWindow();
	virtual void Init(struct GLFWwindow* window) override;

	void MakeCurrent();
	void Render(float deltaTime);

	void Hide();
	void Show();
	bool IsHidden();

	bool Focused();
private:
	// Callback functions for GLFW input events.
	static void WindowFocusCallback(GLFWwindow* window, int focused);
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

	float mScreenWidth = 1200;
	float mScreenHeight = 800;

	static bool bFocused;


};

