#pragma once
class MainWindow
{
public:
	MainWindow();

protected:
	struct GLFWwindow* mWindow;
public:
	virtual void Init(GLFWwindow* window);

	bool ShouldCloseWindow();

	GLFWwindow* GetWindow();
};

