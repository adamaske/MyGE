#include "Scene.h"
#include "Components.h"
void Scene::Init()
{
	CubeMeshRenderComponent r = CubeMeshRenderComponent();
	r.mPosition = glm::vec3(-5, 0, 0);
	mRenderComponents.push_back(r);

	r = CubeMeshRenderComponent();
	r.mPosition = glm::vec3(5, 0, 0);
	mRenderComponents.push_back(r);
}
