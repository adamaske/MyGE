#include "RenderWindow.h"
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Scene.h"
#include "Components.h"

void RenderWindow::Init()
{
	glfwMakeContextCurrent(mWindow);
}

void RenderWindow::Render() {
	

	std::cout << std::endl << std::endl << "-----RenderWindow : Render finished!" << std::endl << std::endl << std::endl;
	
}

void RenderWindow::Close()
{
	glfwSetWindowShouldClose(mWindow, true);
}

bool RenderWindow::ShouldClose()
{
	return glfwWindowShouldClose(mWindow);
}
