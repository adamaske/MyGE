#include "MyGE.h"
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "MainWindow.h"
#include "RenderWindow.h"
#include "Scene.h"

int MyGE::run()
{
    //Init gl
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Our window into the game world is a RenderWindow
    mWindow = new RenderWindow();
    std::cout << "Started init of renderwindow" << std::endl;
    //Init, close if not sucess
    mWindow->Init(glfwCreateWindow(800, 600, "MyGE", NULL, NULL));
    //if () {
    //    std::cout << "Window could not be created!" << std::endl;
    //    //Terminate glfw
    //    glfwSwapBuffers(mWindow->GetWindow());
    //    glfwPollEvents();
    //    //CLose app
    //    return 1;
    //}
    std::cout << "Finished init of renderwindow" << std::endl;
    glfwSwapInterval(1);
    //In this demo I will render 1 secen
    Scene* mScene = new Scene();
    //Init the scene
    mScene->Init();
    //The render window knows what scene to render
    mWindow->SetActiveScene(mScene);
    
    //Main loop
    while (!mWindow->ShouldCloseWindow()) {
        double time = glfwGetTime();
        mWindow->PreRender();
        ProcessInput();
        mWindow->Render();

    }
    
    return 0;
}

void MyGE::ProcessInput()
{
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "Escape Pressed" << std::endl;
        glfwSetWindowShouldClose(mWindow->GetWindow(), true);
    }
}

