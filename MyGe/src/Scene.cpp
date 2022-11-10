#include "Scene.h"
#include <memory>
#include "Shader.h"

void Scene::Init()
{	
	CameraComponent cameraComponent = CameraComponent();
	//Register new GameObject(newID from register)
	int cubeID = Registry::Instance().GetNewID();
	//Create a struct of gameobject called cube
	GameObject cube = { cubeID };
	//Registry Add GameObject to count
	Registry::Instance().RegisterGameObject(cube);
	//Register the components we want to exist
	Registry::Instance().RegisterComponent<CameraComponent>( cameraComponent, cubeID);
	Registry::Instance().RegisterComponent<TransformComponent>();
	Registry::Instance().RegisterComponent<ShaderComponent>();
	Registry::Instance().RegisterComponent<RenderComponent>();
	std::cout << "Scene : Finished Creating Components!" << std::endl;

	
	CameraComponent* camera = Registry::Instance().GetComponent<CameraComponent>(cubeID);
	assert("Asserted");

	//if (!camera) {
	//	
	//	std::cout << "Scene : Init : TEST NEGATIVE" << std::endl;
	//}
	//else {
	//	std::cout << "Scene : Init : TEST POSITIVE" << std::endl;
	//}
	//
	//TransformComponent t =  TransformComponent{};
	//Registry::Instance().AddComponent<TransformComponent>(cubeID, t);
	////Create material and material component
	//int a = cubeID;
	//MaterialComponent material = MaterialComponent{};
	//Registry::Instance().RegisterComponent<MaterialComponent>(material);
	//
	////Mesh component for verts
	//MeshComponent mesh = MeshComponent{};
	////Register meshcomp
	//Registry::Instance().RegisterComponent<MeshComponent>(mesh);
	//
	////RenderComponent for rendering, register it
	//RenderComponent render = RenderComponent{};
	//Registry::Instance().RegisterComponent<RenderComponent>(render);
	//
	////Create a camera
	//int cameraID = Registry::Instance().GetNewID();
	//GameObject camera;
	//Registry::Instance().RegisterGameObject(camera);
	//
	////Transform for the camera
	//TransformComponent cameraTransform = TransformComponent{};
	//Registry::Instance().RegisterComponent<TransformComponent>(cameraTransform, camera.mID);
	//
	////Give camera a camera component
	//CameraComponent cameraComponent = CameraComponent{};
	//Registry::Instance().RegisterComponent<CameraComponent>(cameraComponent, camera.mID);
}


void Scene::OnUpdate() {

	////Gets all GameObjects in the registry, a go system
	auto gameObjects = Registry::Instance().GetGameObjects();
	
	//Prints all gameobject id's
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		std::cout << "Scene : OnUpdate : " << (*it).mID << std::endl;
	}
	
	//Go thorugh camera
	auto cameras = Registry::Instance().GetComponents<CameraComponent>();
	for (auto it = cameras.begin(); it != cameras.end(); it++)
	{
		std::cout << "Scene : OnUpdate : CameraComponent OnUpdate!" << std::endl;
		////Check if it is the main camera
		//if ((*it).bIsMainCamera) {
		//
		//}
	}
	//
	////Go thrugh renderers
	//auto renders = Registry::Instance().GetComponents<RenderComponent>();
	//for (auto it = renders.begin(); it != renders.end(); it++)
	//{
	//	
	//}
}
