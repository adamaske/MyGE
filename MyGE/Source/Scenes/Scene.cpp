#include "pch.h"

#include "Scene.h"

#include "../ShaderManager.h"
#include "../Shader.h"
#include "../Textures/TextureManager.h"
#include "../Textures/Texture.h"
#include "../Systems/System.h"
#include "../Systems/ObjMeshSystem.h"
#include "../Systems/CameraSystem.h"
#include "../Systems/TerrainSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Scripting/NativeScriptingSystem.h"
#include "../Cameras/CameraMovement.h"
#include "../Audio/AudioSystem.h"

Scene::Scene()
{
}

//This is the setup of a scene, what opens when we first open the editor
void Scene::Init()
{
	

}

void Scene::OnUpdate(float deltaTime) {
	
	////Gets all GameObjects in the registry, a go system
	auto gameObjects = Registry::Instance().GetGameObjects();
	//Prints all gameobject id's
	for (auto& go : gameObjects)
	{ 
		
	}

	for (auto system : mSystems)
	{
		system.second->OnUpdate(deltaTime);
	}
}
