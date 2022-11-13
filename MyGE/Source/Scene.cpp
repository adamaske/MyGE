#include "Scene.h"
#include <memory>
#include "Shader.h"
#include "Systems/System.h"
void Scene::Init()
{
	Registry::Instance().RegisterComponent<ShaderComponent>();
	Registry::Instance().RegisterComponent<RenderComponent>();
	Registry::Instance().RegisterComponent<TransformComponent>();
	Registry::Instance().RegisterComponent<MeshComponent>();
	Registry::Instance().RegisterComponent<CameraComponent>();

	std::cout << "Scene started Init!" << std::endl;

	std::string cubePath =		"C:/Users/adama/Documents/GitHub/MyGE/Resources/Meshes/cube.obj";
	std::string monkeyPath =	"C:/Users/adama/Documents/GitHub/MyGE/Resources/Meshes/monkey.obj";

	//Cube gameobject and components
	int cubeID = Registry::Instance().NewGameObject();
	//Create a shader component, should be replaced with material
	auto& shader = Registry::Instance().RegisterComponent<ShaderComponent>(ShaderComponent(), cubeID);
	shader.mShader = mShaderManager.GetShader("PlainShader");
	//Createa render component
	auto& render = Registry::Instance().RegisterComponent<RenderComponent>(RenderComponent(), cubeID);
	//Create a mesh component
	auto& cubeMesh = Registry::Instance().RegisterComponent<MeshComponent>(MeshComponent(), cubeID);
	cubeMesh.mObjFilePath = cubePath;
	auto& cubeTransform = Registry::Instance().GetComponent<TransformComponent>(cubeID);
	cubeTransform.mMatrix = glm::translate(glm::mat4(1), glm::vec3(-2, 0, 1));


	//Monkey gameobject and components
	int monkeyID = Registry::Instance().NewGameObject();
	//Creates a shader component, replace with material component
	ShaderComponent& monkeyShader = Registry::Instance().RegisterComponent<ShaderComponent>(ShaderComponent(), cubeID);
	//Set correct shader
	monkeyShader.mShader = mShaderManager.GetShader("PlainShader");
	//Create render and mesh component, sets path to 
	RenderComponent& monkeyRender = Registry::Instance().RegisterComponent<RenderComponent>(RenderComponent(), monkeyID);
	MeshComponent& monkeyMesh = Registry::Instance().RegisterComponent<MeshComponent>(MeshComponent(), monkeyID); // Register the component to the gameobject
	monkeyMesh.mObjFilePath = monkeyPath;
	TransformComponent& monkeyTransform = Registry::Instance().GetComponent<TransformComponent>(monkeyID);
	monkeyTransform.mMatrix = glm::translate(glm::mat4(1), glm::vec3(2, 0, 1));

	//Camera gameobject and components
	int cameraID = Registry::Instance().NewGameObject();
	CameraComponent& camera = Registry::Instance().RegisterComponent<CameraComponent>(CameraComponent(), cameraID);
	camera.bIsMainCamera = true;
	TransformComponent& cameraTransform = Registry::Instance().GetComponent<TransformComponent>(cameraID);
	cameraTransform.mMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
	//Creating systems
	mSystems.insert({ "ObjMeshSystem", new ObjMeshSystem()});
	mSystems.insert({ "CameraSystem", new CameraMovementSystem() });
	//Init all systems
	for (auto it = mSystems.begin(); it != mSystems.end(); it++)
	{
		//Creating systems
		(*it).second->Init();
	}

	std::cout << "Scene ended Init!" << std::endl;
}


void Scene::OnUpdate(float deltaTime) {
	
	
	////Gets all GameObjects in the registry, a go system
	auto gameObjects = Registry::Instance().GetGameObjects();
	//Prints all gameobject id's
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		std::cout << "Scene : OnUpdate : " << (*it).mID << std::endl;
	}

	//Go thorugh camera
	auto cameras = Registry::Instance().GetComponents<CameraComponent>();
	for (int i = 0; i < cameras.size(); i++)
	{
		std::cout << "Scene : OnUpdate : CameraComponent OnUpdate!" << std::endl;
	
		//Check if it is the main camera
		if (cameras[i]->bIsMainCamera) {
			if (!Registry::Instance().Has<TransformComponent>(cameras[i]->mGameObjectID)) {
				//Camera dosent have a transform
				std::cout << "NO TRANFORM ON CAMERA; RETURNING" << std::endl;
				
			}
			else {

			}
			TransformComponent& transform = Registry::Instance().GetComponent<TransformComponent>(cameras[i]->mGameObjectID);
			auto shader = mShaderManager.GetShader("PlainShader");
			if (shader) {
				std::cout << std::endl << "Scene : OnUpdate : Has a PlainShader : " << shader->mName << std::endl<< std::endl;
			}
			else {
				std::cout << "FOUND NO PLAIN SHADER RETURNING" << std::endl;
				return;
			}
			//Use this shader
			glUseProgram(shader->GetProgram());
			glm::vec3 pos(transform.mMatrix[3].x, transform.mMatrix[3].y, transform.mMatrix[3].z);
			//Update matrices 
			cameras[i]->mProjectionMatrix = glm::perspective(glm::radians(90.f), 1200 / 800.f, 0.1f, 1000.f);
			cameras[i]->mViewMatrix = glm::lookAt(pos, pos + cameras[i]->mForward, glm::vec3(0, 1, 0));
			//Set the variables in the PlainShader
			shader->SetUniformMatrix4(cameras[i]->mViewMatrix, "vMatrix");
			shader->SetUniformMatrix4(cameras[i]->mProjectionMatrix, "pMatrix");
		}
	}


	
	std::cout << "Scene : Systems : OnUpdate started! " << std::endl;
	for (auto it = mSystems.begin(); it != mSystems.end(); it++)
	{
		std::cout << "Scene : OnUpdate : Systems : " << (*it).first << std::endl;
		(*it).second->OnUpdate(deltaTime);
		std::cout << "Scene : OnUpdate : Systems : " << (*it).first << " finished!" << std::endl;
	}
}