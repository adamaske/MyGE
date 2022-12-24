#include "pch.h"
#include "RenderWindow.h"

#include "Scenes/Scene.h"
#include "Components/Components.h"


bool RenderWindow::bFocused = true;
RenderWindow::RenderWindow(){
	
}

void RenderWindow::Init(GLFWwindow* window)
{
	mWindow = window;

	if (mWindow == NULL) {
		Logger::Log("RenderWindow : Failed to create window!", ERROR);
		return;
	}
	//Set callbacks
	glfwSetFramebufferSizeCallback(mWindow, FrameBufferSizeCallback);
	glfwSetWindowFocusCallback(mWindow, WindowFocusCallback);

}

void RenderWindow::MakeCurrent() {
	glfwMakeContextCurrent(mWindow);
}

void RenderWindow::Render(float deltaTime) {
	
}

void RenderWindow::Hide()
{
	glfwHideWindow(mWindow);
}

void RenderWindow::Show()
{
	glfwShowWindow(mWindow);
}

bool RenderWindow::IsHidden()
{
	return !glfwGetWindowAttrib(mWindow, GLFW_VISIBLE);;
}

bool RenderWindow::Focused()
{
	return bFocused;
}

void RenderWindow::WindowFocusCallback(GLFWwindow* window, int focused)
{
	bFocused = focused;
	if (focused) {
		Logger::Log("Got focus");
	}
	else {
		Logger::Log("Lost focus");
	}
}

void RenderWindow::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	//Update what ever camera is rendering to this render window
	glViewport(0, 0, width, height);
}

bool RenderWindow::ShouldCloseWindow()
{
	return false;
}

GLFWwindow* RenderWindow::GetWindow()
{

	return mWindow;
}


