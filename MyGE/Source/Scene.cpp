#include "Scene.h"
#include <memory>
#include "Shader.h"
#include "Systems/System.h"
#include "Camera.h"

void Scene::Init()
{
	Registry::Instance().RegisterComponent<ShaderComponent>();
	Registry::Instance().RegisterComponent<RenderComponent>();
	Registry::Instance().RegisterComponent<TransformComponent>();
	Registry::Instance().RegisterComponent<MeshComponent>();
	Registry::Instance().RegisterComponent<CameraComponent>();
	Registry::Instance().RegisterComponent<MaterialComponent>();
	std::cout << "Scene started Init!" << std::endl;

	std::string cubePath =		"C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGE/Resources/Meshes/cube.obj";
	std::string monkeyPath =	"C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGE/Resources/Meshes/monkey.obj";

#pragma region Create Cube
	std::cout << std::endl << "CREATING CUBE" << std::endl << std::endl;
	//Cube gameobject and components
	uint32_t cubeID = Registry::Instance().NewGameObject();
	//Create a shader component, should be replaced with material
	auto shader = Registry::Instance().RegisterComponent<ShaderComponent>(ShaderComponent(), cubeID);
	shader->mShader = ShaderManager::Instance()->GetShader("PlainShader");
	//Createa render component
	auto cubeRender = Registry::Instance().RegisterComponent<RenderComponent>(RenderComponent(), cubeID);
	cubeRender->mGO= cubeID;
	//Create a mesh component
	auto cubeMesh = Registry::Instance().RegisterComponent<MeshComponent>(MeshComponent(), cubeID);
	cubeMesh->mObjFilePath = cubePath;
	auto cubeMaterial = Registry::Instance().RegisterComponent<MaterialComponent>(MaterialComponent(), cubeID);
	auto cubeTransform = Registry::Instance().GetComponent<TransformComponent>(cubeID);
	cubeTransform->mMatrix = glm::translate(glm::mat4(1), glm::vec3(1, 0, 1));
	std::cout << std::endl << "FINISHED CREATING CUBE" << std::endl << std::endl;
#pragma endregion

#pragma region Create Monkey
	//std::cout << std::endl << "CREATING MONKEY" << std::endl << std::endl;
	////Monkey gameobject and components
	//uint32_t monkeyID = Registry::Instance().NewGameObject();
	////Creates a shader component, replace with material component
	//ShaderComponent& monkeyShader = Registry::Instance().RegisterComponent<ShaderComponent>(ShaderComponent(), monkeyID);
	////Set correct shader
	//monkeyShader.mShader = ShaderManager::Instance()->GetShader("PlainShader");
	////Create render and mesh component, sets path to 
	//RenderComponent& monkeyRender = Registry::Instance().RegisterComponent<RenderComponent>(RenderComponent(), monkeyID);
	//monkeyRender.mGO= monkeyID;
	//MeshComponent& monkeyMesh = Registry::Instance().RegisterComponent<MeshComponent>(MeshComponent(), monkeyID); // Register the component to the gameobject
	//monkeyMesh.mObjFilePath = monkeyPath;
	//TransformComponent& monkeyTransform = Registry::Instance().GetComponent<TransformComponent>(monkeyID);
	//monkeyTransform.mMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, 1));
	//MaterialComponent& monkeyMaterial = Registry::Instance().GetComponent<MaterialComponent>(monkeyID);
	//std::cout << std::endl << "FINISHED CREATING MONKEY" << std::endl << std::endl;
#pragma endregion

#pragma region Create Camera
	std::cout << std::endl << "CREATING CAMERA" << std::endl << std::endl;
	//Camera gameobject and components
	uint32_t cameraID = Registry::Instance().NewGameObject();
	std::cout << "CAMERA ID : " << cameraID << std::endl;
	auto camera = Registry::Instance().RegisterComponent<CameraComponent>(CameraComponent(), cameraID);
	camera->bIsMainCamera = true;
	auto cameraTransform = Registry::Instance().GetComponent<TransformComponent>(cameraID);
	cameraTransform->mMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));

	std::cout << std::endl << "FINISHED CREATING CAMERA" << std::endl << std::endl;
#pragma endregion

	//Creating systems
	mSystems.insert({ "ObjMeshSystem", new ObjMeshSystem()});
	//mSystems.insert({ "CameraControllerSystem", new CameraControllerSystem() });

	//Init all systems
	for (auto system : mSystems)
	{
		//Creating systems
		system.second->Init();
	}

	std::cout << "Scene ended Init!" << std::endl;
}

void Scene::OnUpdate(float deltaTime) {
	
	
	////Gets all GameObjects in the registry, a go system
	auto gameObjects = Registry::Instance().GetGameObjects();
	//Prints all gameobject id's
	for (auto& go : gameObjects)
	{
		std::cout << "Scene : OnUpdate : GameObject " << go << std::endl;
	}

	//We want an array of every camera in the scene
	//If we find a camera whith bisMainCamera  = true, that is the one we want to render the scene view from
	auto cameras = Registry::Instance().GetComponents<CameraComponent>();
	for(auto cam : cameras)
	{
		auto go = (uint32_t)(*cam).mGO;
		//It does find 
		std::cout << "Found camera with objectID " << go << std::endl;
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


	
	std::cout<< std::endl << "SCENE : SYSTEMS ONUPDATE STARTED " << std::endl << std::endl;
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