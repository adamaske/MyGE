#include "pch.h"

#include "Scene.h"

#include "../Shaders/ShaderManager.h"
#include "../Shaders/Shader.h"
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
	
	
}
