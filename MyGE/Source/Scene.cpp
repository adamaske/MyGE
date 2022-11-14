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
	Registry::Instance().RegisterComponent<RigidBodyComponent>();
	Registry::Instance().RegisterComponent<MaterialComponent>();
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
	MaterialComponent& cubeMaterial = Registry::Instance().GetComponent<MaterialComponent>(MaterialComponent(), monkeyID);


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
	MaterialComponent& monkeyMaterial = Registry::Instance().GetComponent<MaterialComponent>(MaterialComponent(), monkeyID);

	//Camera gameobject and components
	int cameraID = Registry::Instance().NewGameObject();
	CameraComponent& camera = Registry::Instance().RegisterComponent<CameraComponent>(CameraComponent(), cameraID);
	camera.bIsMainCamera = true;
	TransformComponent& cameraTransform = Registry::Instance().GetComponent<TransformComponent>(cameraID);
	cameraTransform.mMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
	//Creating systems
	mSystems.insert({ "ObjMeshSystem", new ObjMeshSystem()});
	mSystems.insert({ "CameraControllerSystem", new CameraControllerSystem() });
	mSystems.insert({ "PhysicsSystem", new PhysicsSystem()});
	//Init all systems
	for (auto it = mSystems.begin(); it != mSystems.end(); it++)
	{
		//Creating systems
		(*it).second->Init();
	}

	std::cout << "Scene ended Init!" << std::endl;
}

class GUID {
	GUID() {
		//Generate ID
	};

	uint64_t ID() {
		return mID;
	}
private:
	uint64_t mID;
};

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
		//Check if it is the main camera
		if (cameras[i]->bIsMainCamera) {
			//Gets a transform for the caemra
			TransformComponent& transform = Registry::Instance().GetComponent<TransformComponent>(cameras[i]->mGameObjectID);
			//Get the shader to apply my view and projection matrix
			auto shader = mShaderManager.GetShader("PlainShader");
			//Use this shader
			glUseProgram(shader->GetProgram());
			//Get a position
			glm::vec3 pos(transform.mMatrix[3].x, transform.mMatrix[3].y, transform.mMatrix[3].z);
			//Update matrices 
			cameras[i]->mProjectionMatrix = glm::perspective(glm::radians(90.f), cameras[i]->mAspectRatio, 0.1f, 1000.f);

			cameras[i]->mViewMatrix = glm::lookAt(pos, pos + glm::vec3(0,0, 1), glm::vec3(0, 1, 0));
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

void Scene::ViewportRezised(int width, int height) {
	mViewportWidth = width;
	mViewportHeight = height;
	//GO through all cameras and change their aspect ratio and size 
	auto cameras = Registry::Instance().GetComponents<CameraComponent>();
	for (size_t i = 0; i < cameras.size(); i++)
	{
		//Change cameras without a fixed ar
		if (!cameras[i]->bFixedAsceptRatio) {
			//Remove one of these
			cameras[i]->mCamera.SetViewportSize(width, height);
			cameras[i]->mAspectRatio = (width / height);
		}
	}
}