#include "pch.h"
#include "MainWindow.h"
#include "GLFW/glfw3.h"

MainWindow::MainWindow() : mWindow(nullptr) {
}

void MainWindow::Init(GLFWwindow* window)
{
    mWindow = window;

    //glViewport(0, 0, 800, 600);
    //Make context current
    glfwMakeContextCurrent(mWindow);

}

bool MainWindow::ShouldCloseWindow()
{
    return(glfwWindowShouldClose(mWindow));
}

GLFWwindow* MainWindow::GetWindow()
{
    return mWindow;
}

