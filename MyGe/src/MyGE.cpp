#include "MyGE.h"
#include <iostream>

#include "GLFW/glfw3.h"

#include "MainWindow.h"
#include "RenderWindow.h"
#include "Scene.h"
MyGE::MyGE() {

}

int MyGE::run()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = new RenderWindow();

    if (mWindow->Init(glfwCreateWindow(800, 600, "MyGE", NULL, NULL)) != 0) {
        std::cout << "Window could not be created!" << std::endl;
        //Terminate glfw
        glfwSwapBuffers(mWindow->GetWindow());
        glfwPollEvents();
        //CLose app
        return 1;
    }

    glfwSwapInterval(1);
    
    Scene* mScene = new Scene();
    mScene->Init();
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
        glfwSetWindowShouldClose(mWindow->GetWindow(), true);
    }
}

