#include "MyGE.h"
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "MainWindow.h"
#include "RenderWindow.h"
#include "Scene.h"
#include "ScriptingManager.h"
#include "ShaderManager.h"
#include "Shader.h"

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
    Scene* scene = new Scene();
    //The render window knows what scene to render
    mWindow->SetActiveScene(scene);
    
    //Creates registry instance
    Registry::Instance();

    ScriptingManager scripting = ScriptingManager();
    mScriptingManager = &scripting;
    mScriptingManager->Init();
    
    SceneManager scenemanager = SceneManager();
    mSceneManager = &scenemanager;
    mSceneManager->AddScene(*scene);

    ShaderManager shaderManager = ShaderManager();
    mShaderManager = &shaderManager;

    //Init
    mSceneManager->GetScene()->Init(mShaderManager);
    //The render window knows what scene to render
    mWindow->SetActiveScene(mSceneManager->GetScene());
    //Main loop
    while (!mWindow->ShouldCloseWindow()) {
        double time = glfwGetTime();
        //Process input
        ProcessInput();
        //Change Game
        mSceneManager->GetScene()->OnUpdate();
        
        //Render
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
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "Move forward" << std::endl;
        mSceneManager->GetScene()->MoveForward();
    }
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_N) == GLFW_PRESS) {
        std::cout << "Move forward" << std::endl;
        //Launches new scene
        Scene* s = mSceneManager->GetNextScene(1);
        //Init the scene
        s->Init(mShaderManager);
        //The render window knows what scene to render
        mWindow->SetActiveScene(s);
    }
}


