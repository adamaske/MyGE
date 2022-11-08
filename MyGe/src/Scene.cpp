#include "Scene.h"

void Scene::Init(ShaderManager* shaderManager) 
{
	//Should be removed
	mShaderManager = shaderManager;

	//Create a registry and set it as the current instance
	mRegistry = Registry();
	Registry::SetInstance(mRegistry);

	//Register new GameObject(newID from register)
	int cubeID = Registry::Instance().GetNewID();
	Registry::Instance().Register(GameObject(cubeID));
	
	Registry::Instance().Register<TransformComponent>(TransformComponent(cubeID));
	//Create material and material component
	int a = cubeID;
	MaterialComponent material = MaterialComponent(cubeID);
	Registry::Instance().Register<MaterialComponent>(material);

	//Mesh component for verts
	MeshComponent mesh = MeshComponent(cubeID);
	//Register meshcomp
	Registry::Instance().Register<MeshComponent>(mesh);

	//RenderComponent for rendering, register it
	RenderComponent render = RenderComponent(cubeID);
	Registry::Instance().Register<RenderComponent>(render);

	//Create a camera
	int cameraID = Registry::Instance().GetNewID();
	Registry::Instance().Register<GameObject>(GameObject(cameraID));

	//Transform for the camera
	TransformComponent cameraTransform = TransformComponent(cameraID);
	Registry::Instance().Register<TransformComponent>(cameraTransform);

	//Give camera a camera component
	CameraComponent camera = CameraComponent(cameraID);
	Registry::Instance().Register<CameraComponent>(camera);
}


void Scene::OnUpdate() {
	


	//Gets all GameObjects in the registry, a go system
	auto gameObjects = Registry::Instance().GetObjects<GameObject>();
	//Prints all gameobject id's
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		std::cout << "Scene : OnUpdate : " << (*it).GetID() << std::endl;
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
