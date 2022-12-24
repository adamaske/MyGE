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

void Scene::Init()
{
	
}

void Scene::OnUpdate(float deltaTime) {
	
	
}

void Scene::ViewportRezised(int width, int height) {
	mViewportWidth = width;
	mViewportHeight = height;
	//GO through all cameras and change their aspect ratio and size 
	auto cameras = Registry::Instance().GetComponents<CameraComponent>();
	for (auto& cam : cameras)
	{
		//Change cameras without a fixed ar
		if (!cam->bFixedAsceptRatio) {
			//Remove one of these
			cam->mCamera->SetViewportSize(width, height);
			
			cam->mAspectRatio = ((float)width / (float)height);

		}
	}
}