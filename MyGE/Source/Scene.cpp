#include "Scene.h"
#include <memory>
#include "Shader.h"
#include "Systems/System.h"
void Scene::Init()
{
	Registry::Instance().mName = "BOb";
	std::cout << "REGISTRY NAME  " << Registry::Instance().mName << std::endl;;
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
	mesh.bHasBeenModified = true;
	mesh.mGameObjectID = 1;
	//Gives the mesh the file path to its obj file
	mesh.mObjFilePath = "C:/Users/adama/Documents/GitHub/MyGE/Resources/Meshes/cube.obj";
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
			std::cout << "There is a Main Camera" << std::endl;
			glm::mat4 transform = glm::mat4(1);
			Shader& s = mShaderManager.GetShader("PlainShader");
			s.Use();
			//Update matrices 
			cameras[i]->mProjectionMatrix = glm::perspective(90.f, 16/9.f, 0.1f, 1000.f);
			cameras[i]->mProjectionMatrix = glm::lookAt(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
			//Set the variables in the PlainShader
			s.SetUniformMatrix4(cameras[i]->mProjectionMatrix, "vMatrix");
			s.SetUniformMatrix4(cameras[i]->mProjectionMatrix, "pMatrix");

			std::cout << transform[0].x << transform[0].y << transform[0].z << transform[0].w << std::endl;
			std::cout << transform[1].x << transform[1].y << transform[1].z << transform[1].w << std::endl;
			std::cout << transform[2].x << transform[2].y << transform[2].z << transform[2].w << std::endl;
			std::cout << transform[3].x << transform[3].y << transform[3].z << transform[3].w << std::endl;
		}
	}
	std::cout << "Scene : OnUpdate started! " << std::endl;
	for (auto it = mSystems.begin(); it != mSystems.end(); it++)
	{
		std::cout << "Scene : OnUpdate : Systems : " << (*it).first << std::endl;
		(*it).second->OnUpdate(deltaTime);
		std::cout << "Scene : OnUpdate : Systems : " << (*it).first << " finished!" << std::endl;
	}
	//Go thorugh meshes
	std::cout << "Scene : OnUpdate : Starting to fetch Mesh Componenets!" << std::endl;
	if (!Registry::Instance().Has<MeshComponent>()) {
		std::cout << "Scene : OnUpdate : Registry dosent have a mesh component!";
		return;
	}

	auto meshes = Registry::Instance().GetComponents<MeshComponent>();
	for (int i = 0; i < meshes.size() ; i++)
	{
		//if (!meshes[i]->bHasBeenModified) {
		//	std::cout << " THE MESH COMPONENT IS NOT THE SAME AS THE ONE THAT WAS SPAWNED!" << std::endl;
		//	return;
		//}
		//else {
		//	std::cout << " THE MESH COMPONENT HAS BEEN MODIFIED! THIS PRO " << meshes[i]->mGameObjectID<<  std::endl;
		//}
		std::cout << "Scene : OnUpdate : MeshComponent OnUpdate!" << std::endl;
		auto renderComponent = Registry::Instance().GetComponent<RenderComponent>(meshes[i]->mGameObjectID);
		mShaderManager.GetShader("PlainShader").SetUniformMatrix4(glm::mat4(1), "mMatrix");
		glBindVertexArray(renderComponent.mVAO);
		glDrawElements(GL_TRIANGLES, meshes[i]->mIndices.size(), GL_UNSIGNED_INT, nullptr);
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