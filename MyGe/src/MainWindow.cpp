#include "MainWindow.h"
#include <iostream>
#include "GLFW/glfw3.h"

MainWindow::MainWindow() : mWindow(nullptr) {
}

int MainWindow::Init(GLFWwindow* window)
{
    mWindow = window;
    if (mWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        //glfwTerminate();
        return 1;
    }

    //glViewport(0, 0, 800, 600);
    //Make context current
    glfwMakeContextCurrent(mWindow);

	return 0;
}

bool MainWindow::ShouldCloseWindow()
{
    return(glfwWindowShouldClose(mWindow));
}

GLFWwindow* MainWindow::GetWindow()
{
    return mWindow;
}

