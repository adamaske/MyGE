#include "Scene.h"

void Scene::Init()
{
	//
	std::cout << "Started init of Scene" << std::endl;
	//Create cube
	GameObject* cube1 = new GameObject();
	
	TransformComponent* transform = new TransformComponent(cube1);
	transform->SetPosition(glm::vec3(0, 0, 0));
	//Create material and material component
	MaterialComponent* material = new MaterialComponent(cube1);
	//Plainshader for the material
	shader = new Shader("../plainshader.vert", "../plainshader.frag");
	std::cout << "Shader finished creation!" << std::endl;
	//Add shader to the material
	material->SetShader(shader);
	std::cout << "Material got SHADER!" << std::endl;
	//Mesh component for verts
	MeshComponent* mesh = new MeshComponent(cube1);
	mesh->Init("../src/cube.obj");
	std::cout << "Mesh finished init!" << std::endl;
	RenderComponent* render = new RenderComponent(cube1);
	render->Init(mesh, transform, material);
	//Create a camera
	GameObject* mCamera = new GameObject();
	std::cout << "Finished camera creation!" << std::endl;
	//Transform for the camera
	transform = new TransformComponent(mCamera);
	std::cout << "Camera Transform finished creation!" << std::endl;
	//Moves camera to desired position
	transform->SetPosition(glm::vec3(0, 0, -10));
	//Give camera a camera component
	CameraComponent* camera = new CameraComponent(mCamera);
	
	mCamera->AddComponent(transform);
	mCamera->AddComponent(camera);

	mActiveCamera = camera;
	std::cout << "Finished init of Scene" << std::endl;

	mObjects.push_back(mCamera);
	mObjects.push_back(cube1);

	mRenders.push_back(render);
}


void Scene::OnUpdate() {

	for (int i = 0; i < mObjects.size(); i++)
	{
		mObjects[i]->OnUpdate();
	}
}
