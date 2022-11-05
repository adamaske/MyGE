#pragma once
class MainWindow
{
public:
	MainWindow();

protected:
	struct GLFWwindow* mWindow;
public:
	virtual int Init(GLFWwindow* window);

	bool ShouldCloseWindow();

	GLFWwindow* GetWindow();
};

