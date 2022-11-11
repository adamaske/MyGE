#include "Scene.h"
#include <memory>
#include "Shader.h"
#include "Systems/System.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
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
	mesh.mObjFilePath = "C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGE/Resources/Meshes/cube.obj";
	//Register new GameObject(newID from register)
	int cubeID = Registry::Instance().GetNewID();
	std::cout << "CUBE ID == " << cubeID << std::endl;
	//Create a struct of gameobject called cube
	GameObject cube = { cubeID };
	//Registry Add GameObject to count
	Registry::Instance().RegisterGameObject(cube);
	mCameraID = Registry::Instance().GetNewID();
	GameObject cameraGO = { mCameraID };
	Registry::Instance().RegisterGameObject(cameraGO);
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
			glm::vec3 direction;
			direction.x = cos(glm::radians(cameras[i]->mYaw)) * cos(glm::radians(cameras[i]->mPitch));
			direction.y = sin(glm::radians(cameras[i]->mPitch));
			direction.z = sin(glm::radians(cameras[i]->mYaw)) * cos(glm::radians(cameras[i]->mPitch));

			cameras[i]->mForward = direction;
			cameras[i]->mPosition = glm::vec3(transform.mMatrix[3].x, transform.mMatrix[3].y, transform.mMatrix[3].z);
			cameras[i]->mForward = glm::normalize(glm::vec3(cameras[i]->mTarget - cameras[i]->mPosition));
			glm::vec3 up{ 0.f, 1.f, 0.f };
			cameras[i]->mRight = glm::normalize(glm::cross(cameras[i]->mForward, up));
			cameras[i]->mUp = glm::normalize(glm::cross(cameras[i]->mForward, -cameras[i]->mRight));
			//Update matrices 
			cameras[i]->mProjectionMatrix = glm::perspective(90.f, 16.f / 9.f, 0.1f, 1000.f);
			cameras[i]->mViewMatrix = glm::lookAt(cameras[i]->mPosition, cameras[i]->mPosition + cameras[i]->mForward, glm::vec3(0, 1, 0));
			//Set the variables in the PlainShader
			shader->SetUniformMatrix4(cameras[i]->mViewMatrix, "vMatrix");
			shader->SetUniformMatrix4(cameras[i]->mProjectionMatrix, "pMatrix");
		}
	}


	
	std::cout << "Scene : OnUpdate started! " << std::endl;
	for (auto it = mSystems.begin(); it != mSystems.end(); it++)
	{
		std::cout << "Scene : OnUpdate : Systems : " << (*it).first << std::endl;
		(*it).second->OnUpdate(deltaTime);
		std::cout << "Scene : OnUpdate : Systems : " << (*it).first << " finished!" << std::endl;
	}

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