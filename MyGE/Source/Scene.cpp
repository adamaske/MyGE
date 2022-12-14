#include "pch.h"

#include "Scene.h"

#include "Shader.h"

#include "Systems/System.h"
#include "Systems/ObjMeshSystem.h"
#include "Systems/CameraSystem.h"
#include "Systems/TerrainSystem.h"
#include "Systems/RenderSystem.h"
#include "Textures/TextureManager.h"
#include "Textures/Texture.h"

#include "Scripting/NativeScriptingSystem.h"

Scene::Scene()
{
}

void Scene::Init()
{
	//Registering all components, this can be remvoed
	Registry::Instance().RegisterComponent<RenderComponent>();
	Registry::Instance().RegisterComponent<TransformComponent>();
	Registry::Instance().RegisterComponent<MeshComponent>();
	Registry::Instance().RegisterComponent<CameraComponent>();
	Registry::Instance().RegisterComponent<MaterialComponent>();
	Registry::Instance().RegisterComponent<AudioSourceComponent>();
	Registry::Instance().RegisterComponent<AudioListenerComponent>();
	Registry::Instance().RegisterComponent<TerrainComponent>();
	Registry::Instance().RegisterComponent<NativeScriptComponent>();

	//File path for obj meshses
	std::string cubePath =		"../Resources/Meshes/cube.obj";
	std::string monkeyPath =	"../Resources/Meshes/monkey.obj";

#pragma region Create Cube
	//Cube gameobject and components
	uint32_t cubeID = Registry::Instance().NewGameObject();
	//Create a shader component, should be replaced with material
	
	//Createa render component
	auto cubeRender = Registry::Instance().RegisterComponent<RenderComponent>(RenderComponent(), cubeID);
	cubeRender->mGO= cubeID;
	//Create a mesh component
	auto cubeMesh = Registry::Instance().RegisterComponent<MeshComponent>(MeshComponent(), cubeID);
	cubeMesh->mObjFilePath = cubePath;
	cubeMesh->mMeshName = "Cube";
	//Material
	auto cubeMaterial = Registry::Instance().RegisterComponent<MaterialComponent>(MaterialComponent(), cubeID);
	cubeMaterial->mShader = ShaderManager::Instance()->GetShader("PlainShader");
	cubeMaterial->mTexture = TextureManager::GetTexture("HammerTexture");
	auto cubeTransform = Registry::Instance().GetComponent<TransformComponent>(cubeID);
	cubeTransform->mMatrix = glm::translate(glm::mat4(1), glm::vec3(1, 0, 1));

	auto cubeSource = Registry::Instance().RegisterComponent<AudioSourceComponent>(AudioSourceComponent(), cubeID);
	cubeSource->mName = "Explosion";
	cubeSource->mFilePath = "";
	cubeSource->bShouldPlay = true;
	cubeSource->mGain = 1;
#pragma endregion

#pragma region Create Monkey
	//Monkey gameobject and components
	uint32_t monkeyID = Registry::Instance().NewGameObject();
	//Create render and mesh component, sets path to 
	auto monkeyRender = Registry::Instance().RegisterComponent<RenderComponent>(RenderComponent(), monkeyID);
	monkeyRender->mGO = monkeyID;
	auto monkeyMesh = Registry::Instance().RegisterComponent<MeshComponent>(MeshComponent(), monkeyID); // Register the component to the gameobject
	monkeyMesh->mObjFilePath = monkeyPath;
	monkeyMesh->mMeshName = "Monkey";
	auto monkeyTransform = Registry::Instance().GetComponent<TransformComponent>(monkeyID);
	monkeyTransform->mMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, 1));
	//Material
	auto monkeyMaterial = Registry::Instance().GetComponent<MaterialComponent>(monkeyID);
	monkeyMaterial->mShader = ShaderManager::Instance()->GetShader("TextureShader");
	monkeyMaterial->mTexture = TextureManager::GetTexture("HammerTexture");
#pragma endregion

#pragma region Create Camera
	//Camera gameobject and components
	uint32_t cameraID = Registry::Instance().NewGameObject();
	auto camera = Registry::Instance().RegisterComponent<CameraComponent>(CameraComponent(), cameraID);
	camera->bIsMainCamera = true;
	auto cameraTransform = Registry::Instance().GetComponent<TransformComponent>(cameraID);
	cameraTransform->mMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
#pragma endregion

#pragma region Create Terrain
	auto terrainID = Registry::Instance().NewGameObject();

	auto terrain = Registry::Instance().RegisterComponent<TerrainComponent>(TerrainComponent(), terrainID);
	terrain->mType = TerrainComponent::TerrainType::PerlinNoise;



#pragma endregion

#pragma region NativeScripting
	auto go = Registry::Instance().NewGameObject();

	auto ns = Registry::Instance().RegisterComponent<NativeScriptComponent>(NativeScriptComponent(), go);
	//This should now instantiate a Monkey(), and the mObejct i ns is now that Monkey, and everything should work
	ns->Bind<Monkey>();

#pragma endregion

#pragma region Systems
	//Creating systems
	mSystems.insert({ "RednerSystem", new RenderSystem() });
	mSystems.insert({ "ObjMeshSystem", new ObjMeshSystem()});
	mSystems.insert({ "TerrainSystem", new TerrainSystem() });
	mSystems.insert({ "CameraSystem" , new CameraSystem() });
	mSystems.insert({ "NativeScriptingSystem", new NativeScriptingSystem() });
	//mSystems.insert({ "CameraControllerSystem", new CameraControllerSystem() });

	//Init all systems
	for (auto system : mSystems)
	{
		//Creating systems
		system.second->Init();
	}
#pragma endregion
}

void Scene::OnUpdate(float deltaTime) {
	
	
	////Gets all GameObjects in the registry, a go system
	auto gameObjects = Registry::Instance().GetGameObjects();
	//Prints all gameobject id's
	for (auto& go : gameObjects)
	{ 

	}

	//We want an array of every camera in the scene
	//If we find a camera whith bisMainCamera  = true, that is the one we want to render the scene view from
	auto cameras = Registry::Instance().GetComponents<CameraComponent>();
	for(auto cam : cameras)
	{
		auto go = (uint32_t)(*cam).mGO;
		//It does find 
		//Check if it is the main camera
		if (cam->bIsMainCamera) {
			//Gets a transform for the camera
			auto transform = Registry::Instance().GetComponent<TransformComponent>(go);
			//Get the shader to apply my view and projection matrix
			auto shader = ShaderManager::Instance()->GetShader("PlainShader");
			//Use this shader
			shader->Use();
			//Get a position
			glm::vec3 pos(transform->mMatrix[3].x, transform->mMatrix[3].y, transform->mMatrix[3].z);
			//Update matrices 
			cam->mProjectionMatrix = glm::perspective(glm::radians(90.f), cam->mAspectRatio, 0.1f, 1000.f);

			cam->mViewMatrix = glm::lookAt(pos, pos + glm::vec3(0,0, 1), glm::vec3(0, 1, 0));
			//Set the variables in the PlainShader
			shader->SetUniformMatrix4(cam->mViewMatrix, "vMatrix");
			shader->SetUniformMatrix4(cam->mProjectionMatrix, "pMatrix");
		}
	}

	for (auto system : mSystems)
	{
		system.second->OnUpdate(deltaTime);
	}
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
			cam->mCamera.SetViewportSize(width, height);
			cam->mAspectRatio = ((float)width / (float)height);
		}
	}
}