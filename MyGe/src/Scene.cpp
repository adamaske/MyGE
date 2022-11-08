#include "Scene.h"

void Scene::Init(ShaderManager* shaderManager) 
{
	//Should be removed
	mShaderManager = shaderManager;
	
	//Create a registry and set it as the current instance
	
	mRegistry = Registry::Instance();
	//Register the components we want to exist
	Registry::Instance().RegisterComponent<CameraComponent>();
	Registry::Instance().RegisterComponent<TransformComponent>();
	Registry::Instance().RegisterComponent<ShaderComponent>();
	Registry::Instance().RegisterComponent<RenderComponent>();
	
	//Register new GameObject(newID from register)
	int cubeID = Registry::Instance().GetNewID();
	//Create a struct of gameobject called cube
	GameObject cube = { cubeID };
	//Registry Add GameObject to count
	Registry::Instance().RegisterGameObject<GameObject>(cube, cubeID);
	//Registry::Instance().AddGameObject<GameObject>(cube, cubeID);
	
	TransformComponent t =  TransformComponent{};
	Registry::Instance().AddComponent<TransformComponent>(cubeID, t);
	//Create material and material component
	int a = cubeID;
	MaterialComponent material = MaterialComponent{};
	Registry::Instance().Register<MaterialComponent>(material);
	
	//Mesh component for verts
	MeshComponent mesh = MeshComponent{};
	//Register meshcomp
	Registry::Instance().Register<MeshComponent>(mesh);
	
	//RenderComponent for rendering, register it
	RenderComponent render = RenderComponent{};
	Registry::Instance().Register<RenderComponent>(render);
	
	//Create a camera
	int cameraID = Registry::Instance().GetNewID();
	Registry::Instance().Register<GameObject>(GameObject());
	
	//Transform for the camera
	TransformComponent cameraTransform = TransformComponent{};
	Registry::Instance().Register<TransformComponent>(cameraTransform);
	
	//Give camera a camera component
	CameraComponent camera = CameraComponent{};
	Registry::Instance().Register<CameraComponent>(camera);
}


void Scene::OnUpdate() {

	//Gets all GameObjects in the registry, a go system
	Registry::Instance().GetObjects<RenderComponent>();
	auto gameObjects = .GetObjects<GameObject>();
	//Prints all gameobject id's
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		std::cout << "Scene : OnUpdate : " << (*it).mID << std::endl;
	}
	
	//Go thorugh camera
	auto cameras = Registry::Instance().GetObjects<CameraComponent>();
	for (auto it = cameras.begin(); it != cameras.end(); it++)
	{
		//Check if it is the main camera
		if ((*it).bIsMainCamera) {
	
		}
	}
	
	//Go thrugh renderers
	auto renders = Registry::Instance().GetObjects<RenderComponent>();
	for (auto it = renders.begin(); it != renders.end(); it++)
	{
	
	}
}
