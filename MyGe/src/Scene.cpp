#include "Scene.h"
#include "Components.h"
#include "GameObject.h"
void Scene::Init()
{

	//Create game object
	GameObject* cube1 = new GameObject();
	GameObject* cube2 = new GameObject();

	cube1->AddComponent(new TransformComponent(cube1));
	cube2->AddComponent(new TransformComponent(cube2));

	cube1->AddComponent(new MeshComponent(cube1));
	cube2->AddComponent(new MeshComponent(cube2));

	cube1->AddComponent(new MaterialComponent(cube1));
	cube2->AddComponent(new MaterialComponent(cube2));

	
}
