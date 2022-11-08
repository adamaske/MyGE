#include "Scene.h"

void Scene::Init(ShaderManager* shaderManager) 
{
	mShaderManager = shaderManager;

	//Create cube
	int cubeID = Registry::Instance().GetObjectID();
	Registry::Instance().Register(GameObject(cubeID));
	
	
	Registry::Instance().Register<TransformComponent>(TransformComponent(Registry::Instance().GetObjectID()));
	transform->SetPosition(glm::vec3(1, 1, 1));
	//Create material and material component
	MaterialComponent* material = new MaterialComponent();
	material->SetShader(&mShaderManager->GetShader("PlainShader"));
	//Plainshader for the material

	//Add shader to the material
	material->SetShader(&mShaderManager->GetShader("PlainShader"));

	//Mesh component for verts
	MeshComponent* mesh = new MeshComponent(&cube1);
	mesh->Init("C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGe/MyGe/src/cube.obj");

	RenderComponent* render = new RenderComponent(&cube1);
	render->Init(mesh, transform, material);

	//Create a camera
	GameObject* mCamera = new GameObject();

	//Transform for the camera
	TransformComponent* transform2 = new TransformComponent(mCamera);

	//Moves camera to desired position
	transform2->SetPosition(glm::vec3(0, 0, -5));
	//Give camera a camera component
	CameraComponent* camera = new CameraComponent(mCamera);
	camera->Init(transform2);

	mCamera->AddComponent(transform2);
	mCamera->AddComponent(camera);

	mActiveCamera = camera;

	mObjects["Camera"] = mCamera;
	mObjects["Cube1"] = &cube1;
	
	mCamera->Init();
	cube1.Init();
	mRenders.push_back(render);
}


void Scene::OnUpdate() {
	mActiveCamera->LookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 2), glm::vec3(0, 0, 1));
	mShaderManager->GetCamera(mActiveCamera->GetViewMatrix(), mActiveCamera->GetProjectionMatrix());
	for (auto it = mObjects.begin(); it != mObjects.end(); it++)
	{
		std::cout << "Scene : OnUpdate" << std::endl;
		(*it).second->OnUpdate();
	}
}
