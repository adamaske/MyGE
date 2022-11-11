#include "Scene.h"
#include <memory>
#include "Shader.h"
#include "Systems/System.h"
void Scene::Init()
{
	CameraComponent cameraComponent = CameraComponent();
	cameraComponent.bIsMainCamera = true;
	TransformComponent	transform = TransformComponent();

	//Create a shader component, should be replaced with material
	ShaderComponent		shader = ShaderComponent();
	//Give the shader component the plain shader
	shader.mShader = mShaderManager.GetShader("PlainShader");
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
			if (!Registry::Instance().Has<TransformComponent>(cameras[i]->mGameObjectID)) {
				//Camera dosent have a transform
				std::cout << "NO TRANFORM ON CAMERA; RETURNING" << std::endl;
				return;
			}
			else {

			}
			auto transform = Registry::Instance().GetComponent<TransformComponent>(cameras[i]->mGameObjectID);
			std::cout << "There is a Main Camera" << std::endl;
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
			//Update matrices 
			cameras[i]->mProjectionMatrix = glm::perspective(120.f, 800.f/600.f, 0.1f, 1000.f);
			cameras[i]->mViewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0,0,1), glm::vec3(0, 1, 0));
			//Set the variables in the PlainShader
			shader->SetUniformMatrix4(cameras[i]->mViewMatrix, "vMatrix");
			shader->SetUniformMatrix4(cameras[i]->mProjectionMatrix, "pMatrix");
		}
	}


	auto meshes = Registry::Instance().GetComponents<MeshComponent>();
	for (int i = 0; i < meshes.size(); i++)
	{

		std::cout << "Scene : OnUpdate : MeshComponent OnUpdate!" << std::endl;
		//Get a render component from this meshcomponent
		auto renderComponent = Registry::Instance().GetComponent<RenderComponent>(meshes[i]->mGameObjectID);
		//Get a shader component from this mesh component
		auto shader = mShaderManager.GetShader("PlainShader");
		//If we found th ehsdaer "Plainshader
		if (!shader) {
			std::cout << "Did not find shader, returning" << std::endl;
			return;
		}

		//Use the shader

		glm::mat4 mPos = glm::translate(glm::mat4(1), glm::vec3(0,0,1));
		glm::mat4 mRot = glm::mat4(1);
		glm::mat4 mScale = glm::mat4(1);
		glm::mat4 matrix = mPos * mRot * mScale;;
		if (!Registry::Instance().Has<TransformComponent>(meshes[i]->mGameObjectID)) {
			//There is no transform connected with this scene
		}
		auto transfrom = Registry::Instance().GetComponent<TransformComponent>(meshes[i]->mGameObjectID);
	
		shader->SetUniformMatrix4(matrix, "mMatrix");
		
		glBindVertexArray(renderComponent.mVAO);

		glDrawElements(GL_TRIANGLES, meshes[i]->mIndices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		std::cout << "RenderComponent : Render End!" << std::endl;
	}
	//std::cout << "Scene : OnUpdate started! " << std::endl;
	//for (auto it = mSystems.begin(); it != mSystems.end(); it++)
	//{
	//	std::cout << "Scene : OnUpdate : Systems : " << (*it).first << std::endl;
	//	(*it).second->OnUpdate(deltaTime);
	//	std::cout << "Scene : OnUpdate : Systems : " << (*it).first << " finished!" << std::endl;
	//}
	////Go thorugh meshes
	//std::cout << "Scene : OnUpdate : Starting to fetch Mesh Componenets!" << std::endl;
	//if (!Registry::Instance().Has<MeshComponent>()) {
	//	std::cout << "Scene : OnUpdate : Registry dosent have a mesh component!";
	//	return;
	//}

	//
	////Go thrugh renderers
	//auto renders = Registry::Instance().GetComponents<RenderComponent>();
	//for (auto it = renders.begin(); it != renders.end(); it++)
	//{
	//	
	//}
}