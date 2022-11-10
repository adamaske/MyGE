#include "Scene.h"
#include <memory>
#include "Shader.h"
#include "System.h"
void Scene::Init()
{

	CameraComponent cameraComponent = CameraComponent();
	cameraComponent.bIsMainCamera = true;
	TransformComponent	transform = TransformComponent();

	//Create a shader component, should be replaced with material
	ShaderComponent		shader = ShaderComponent();
	//Give the shader component the plain shader
	shader.mShader = &mShaderManager.GetShader("PlainShader");
	//Createa render component
	RenderComponent		render = RenderComponent();
	//Create a mesh component
	MeshComponent		mesh = MeshComponent();
	//Gives the mesh the file path to its obj file
	mesh.mObjFilePath = "C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGE/MyGE/src/cube.obj";
	//Register new GameObject(newID from register)
	int cubeID = Registry::Instance().GetNewID();
	std::cout << "CUBE ID == " << cubeID << std::endl;
	//Create a struct of gameobject called cube
	GameObject cube = { cubeID };
	//Registry Add GameObject to count
	Registry::Instance().RegisterGameObject(cube);

	//Register the components we want to exist
	Registry::Instance().RegisterComponent<CameraComponent>(cameraComponent, cubeID);
	Registry::Instance().RegisterComponent<TransformComponent>(transform, cubeID);
	Registry::Instance().RegisterComponent<ShaderComponent>(shader, cubeID);
	Registry::Instance().RegisterComponent<RenderComponent>(render, cubeID);
	Registry::Instance().RegisterComponent<MeshComponent>(mesh, cubeID);

	std::cout << "Scene : Finished Creating Components!" << std::endl;


	CameraComponent& camera = Registry::Instance().GetComponent<CameraComponent>(cubeID);
	std::cout << "Scene : Init : Created CameraComponent" << std::endl;
	//Creating systems
	//System for creating mesh from files nad rendering them
	mObjMeshSystem = new ObjMeshSystem();

	mSystems.insert({ "ObjMeshSystem", mObjMeshSystem });
	for (auto it = mSystems.begin(); it != mSystems.end(); it++)
	{
		std::cout << "Scene : Init : " << (*it).first << std::endl;
		//Creating systems
		(*it).second->Init();
		std::cout << "Scene : Finished Init : " << (*it).first << std::endl;
	}

}


void Scene::OnUpdate(float deltaTime) {
	std::cout << "Scene : OnUpdate started! " << std::endl;
	for (auto it = mSystems.begin(); it != mSystems.end(); it++)
	{
		std::cout << "Scene : OnUpdate : Systems : " << (*it).first << std::endl;
		(*it).second->OnUpdate(deltaTime);
		std::cout << "Scene : OnUpdate : Systems : " << (*it).first << " finished!" << std::endl;
	}

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
		//Check if it is the main camera
		if ((*it)->bIsMainCamera) {
			Shader& s = mShaderManager.GetShader("PlainShader");
			s.SetUniformMatrix4((*it)->mViewMatrix, "vMatrix");
			s.SetUniformMatrix4((*it)->mProjectionMatrix, "pMatrix");
		}
	}
	//Go thorugh meshes
	auto meshes = Registry::Instance().GetComponents<MeshComponent>();
	for (auto it = meshes.begin(); it != meshes.end(); it++)
	{
		std::cout << "Scene : OnUpdate : MeshComponent OnUpdate!" << std::endl;
		RenderComponent& renderComponent = Registry::Instance().GetComponent<RenderComponent>((*it)->mGameObjectID);
		glBindVertexArray(renderComponent.mVAO);
		glDrawElements(GL_TRIANGLES, (*it)->mIndices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		std::cout << "RenderComponent : Render End!" << std::endl;
	}
	//
	////Go thrugh renderers
	//auto renders = Registry::Instance().GetComponents<RenderComponent>();
	//for (auto it = renders.begin(); it != renders.end(); it++)
	//{
	//	
	//}
}