#include "pch.h"
#include "MonkeyScene.h"
#include "Scene.h"

#include "../RenderWindow.h"

#include "../Shaders/ShaderManager.h"

#include "../Systems/System.h"
#include "../Systems/CameraSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/TerrainSystem.h"
#include "../Scripting/NativeScriptingSystem.h"
//Editor systems
#include "../Systems/EditorSystems/QuickCreateObjectsSystem.h"
//#include "../Systems/EditorSystems/SceneViewSystem.h"
//#include "../Systems/EditorSystems/GameViewSystem.h"

#include "../Cameras/Camera.h"
#include "../Cameras/CameraMovement.h"
//#include "../Cameras/EditorCamera.h"

#include "../Textures/Texture.h"
#include "../Textures/TextureManager.h"
MonkeyScene::MonkeyScene()
{
}

void MonkeyScene::Init()
{
	Logger::Log("MONKEYSCENE INIT");
	//File path for obj meshses
	std::string cubePath = "../Resources/Meshes/cube.obj";
	std::string monkeyPath = "../Resources/Meshes/monkey.obj";

#pragma region Create Cube
	//Cube gameobject and components
	uint32_t cubeID = Registry::Instance().NewGameObject();
	//Create a shader component, should be replaced with material

	//Create a mesh component
	auto cubeMesh = Registry::Instance().RegisterComponent<MeshComponent>(MeshComponent(), cubeID);
	cubeMesh->mObjFilePath = cubePath;
	//Material
	auto cubeMaterial = Registry::Instance().RegisterComponent<MaterialComponent>(MaterialComponent(), cubeID);
	cubeMaterial->mShader = ShaderManager::Instance()->GetShader("MyGEShader");
	cubeMaterial->mTexture = TextureManager::GetTexture("LavaDiffuse");
	auto cubeTransform = Registry::Instance().GetComponent<TransformComponent>(cubeID);
	cubeTransform->mMatrix = glm::translate(glm::mat4(1), glm::vec3(1, 0, 1));

	auto cubeSource = Registry::Instance().RegisterComponent<AudioSourceComponent>(AudioSourceComponent(), cubeID);
	cubeSource->mName = "Explosion";
	cubeSource->mFilePath = "../Resources/Audio/explosion.obj";
	cubeSource->bShouldPlay = true;
	cubeSource->mGain = 1;
#pragma endregion

#pragma region Create Monkey
	//Monkey gameobject and components
	uint32_t monkeyID = Registry::Instance().NewGameObject();
	//Create render and mesh component, sets path to 
	auto monkeyMesh = Registry::Instance().RegisterComponent<MeshComponent>(MeshComponent(), monkeyID); // Register the component to the gameobject
	monkeyMesh->mObjFilePath = monkeyPath;
	auto monkeyTransform = Registry::Instance().GetComponent<TransformComponent>(monkeyID);
	monkeyTransform->mMatrix = glm::translate(glm::mat4(1), glm::vec3(-1, 0, 0));

	auto monkeyMaterial = Registry::Instance().GetComponent<MaterialComponent>(monkeyID);
	monkeyMaterial->mShader = ShaderManager::Instance()->GetShader("MyGEShader");
	monkeyMaterial->mTexture = TextureManager::GetTexture("LavaDiffuse");
#pragma endregion

#pragma region Create Game Camera
	//Camera gameobject and components
	uint32_t cameraID = Registry::Instance().NewGameObject();
	auto camera = Registry::Instance().RegisterComponent<CameraComponent>(CameraComponent(), cameraID);
	camera->mTargetOffset = glm::vec3(0, -5, 5);
	camera->bIsMainCamera = true;
	auto cameraTransform = Registry::Instance().GetComponent<TransformComponent>(cameraID);
	cameraTransform->mMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 10, -10));
	
	//This gives the camera a CameraMovement script, which handles input and etc for the camera, this is 
	auto cameraMovementScript = Registry::Instance().RegisterComponent<NativeScriptComponent>(NativeScriptComponent(), cameraID);
	cameraMovementScript->Bind<CameraMovement>();
#pragma endregion

#pragma region Create Terrain
	auto terrainID = Registry::Instance().NewGameObject();

	auto terrain = Registry::Instance().RegisterComponent<TerrainComponent>(TerrainComponent(), terrainID);
	terrain->mType = TerrainComponent::TerrainType::PerlinNoise;

	//Add grass texture to the terrain
	auto terrainMaterial = Registry::Instance().GetComponent<MaterialComponent>(terrainID);
	terrainMaterial->mTexture = TextureManager::GetTexture("GrassDiffuse");
	terrainMaterial->mShader = ShaderManager::Instance()->GetShader("MyGEShader");

	auto terrainTransform = Registry::Instance().GetComponent<TransformComponent>(terrainID);
	float x = -terrain->mWidth / 2.f;
	float z = -terrain->mHeight / 2.f;
	terrainTransform->mMatrix = glm::translate(glm::mat4(1), glm::vec3(x, 0, z));
#pragma endregion

#pragma region NativeScripting
	auto go = Registry::Instance().NewGameObject();

	auto ns = Registry::Instance().RegisterComponent<NativeScriptComponent>(NativeScriptComponent(), go);
	//This should now instantiate a Monkey(), and the mObejct i ns is now that Monkey, and everything should work
	ns->Bind<Monkey>();

#pragma endregion
}

void MonkeyScene::OnUpdate(float deltaTime)
{

	//Lol ? 
}