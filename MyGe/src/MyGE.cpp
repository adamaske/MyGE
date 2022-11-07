#include "MyGE.h"
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "MainWindow.h"
#include "RenderWindow.h"
#include "Scene.h"


bool CheckLua(lua_State* L, int r) {
    if (r != LUA_OK) {
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
        return false;
    }
    return true;
}

MyGE::MyGE() {
    
}
int MyGE::run()
{
    //Init gl
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Our window into the game world is a RenderWindow
    mWindow = new RenderWindow();
    //Init, close if not sucess
    mWindow->Init(glfwCreateWindow(800, 600, "MyGE", NULL, NULL));
 
    glfwSwapInterval(1);
    //In this demo I will render 1 secen
    mActiveScene = new Scene();
    //Init the scene
    mActiveScene->Init();
    //The render window knows what scene to render
    mWindow->SetActiveScene(mActiveScene);
    
    //Main loop
    while (!mWindow->ShouldCloseWindow()) {
        double time = glfwGetTime();
        mActiveScene->OnUpdate();
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

