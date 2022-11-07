#include "Scene.h"

void Scene::Init(ShaderManager* shaderManager) 
{
	mShaderManager = shaderManager;
	std::cout << "Started init of Scene" << std::endl;
	//Create cube
	GameObject* cube1 = new GameObject();
	
	TransformComponent* transform = new TransformComponent(cube1);
	transform->SetPosition(glm::vec3(1, 1, 1));
	//Create material and material component
	MaterialComponent* material = new MaterialComponent(cube1);
	material->SetShader(&mShaderManager->GetShader("PlainShader"));
	//Plainshader for the material
	std::cout << "Shader finished creation!" << std::endl;
	//Add shader to the material
	material->SetShader(&mShaderManager->GetShader("PlainShader"));
	std::cout << "Material got SHADER!" << std::endl;
	//Mesh component for verts
	MeshComponent* mesh = new MeshComponent(cube1);
	mesh->Init("C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGe/MyGe/src/cube.obj");
	std::cout << "Mesh finished init!" << std::endl;
	RenderComponent* render = new RenderComponent(cube1);
	render->Init(mesh, transform, material);

	//Create a camera
	GameObject* mCamera = new GameObject();
	std::cout << "Finished camera creation!" << std::endl;
	//Transform for the camera
	TransformComponent* transform2 = new TransformComponent(mCamera);
	std::cout << "Camera Transform finished creation!" << std::endl;
	//Moves camera to desired position
	transform2->SetPosition(glm::vec3(0, 0, -5));
	//Give camera a camera component
	CameraComponent* camera = new CameraComponent(mCamera);
	camera->Init(transform2);
	mCamera->AddComponent(transform2);
	mCamera->AddComponent(camera);

	mActiveCamera = camera;
	std::cout << "Finished init of Scene" << std::endl;

	mObjects["Camera"] = mCamera;
	mObjects["Cube1"] = cube1;
	
	mCamera->Init();
	camera->LookAt(glm::vec3(-2, 0, 1), glm::vec3(-2, 0, 1), glm::vec3(-2, 0, 1));
	cube1->Init();
	mRenders.push_back(render);
}


void Scene::OnUpdate() {

	mShaderManager->GetCamera(mActiveCamera->GetViewMatrix(), mActiveCamera->GetProjectionMatrix());
	mActiveCamera->LookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 2), glm::vec3(0, 0, 1));
	

	mShaderManager->GetCamera(mActiveCamera->GetViewMatrix(), mActiveCamera->GetProjectionMatrix());
	for (auto it = mObjects.begin(); it != mObjects.end(); it++)
	{
		std::cout << "Scene : OnUpdate" << std::endl;
		(*it).second->OnUpdate();
	}
}
