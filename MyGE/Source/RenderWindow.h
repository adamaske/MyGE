#pragma once
class RenderWindow
{
public:
	RenderWindow();
	void Init(struct GLFWwindow* window);

	void MakeCurrent();
	void Render(float deltaTime);

	void Hide();
	void Show();
	bool IsHidden();

	bool Focused();

	bool ShouldCloseWindow();

	GLFWwindow* GetWindow();

private:
	// Callback functions for GLFW input events.
	static void WindowFocusCallback(GLFWwindow* window, int focused);
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

	float mScreenWidth = 1200;
	float mScreenHeight = 800;

	static bool bFocused;


	struct GLFWwindow* mWindow;

};

