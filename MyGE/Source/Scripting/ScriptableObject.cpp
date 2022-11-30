#include "ScriptableObject.h"
#include "../Registry.h"
#include "../Components/Components.h"

#include <iostream>

template<class T>
std::shared_ptr<T> ScriptableObject::AddComponent()
{
	auto comp = Registry::Instance().RegisterComponent<T>(T(), mGO);
	return comp;
}

template<class T>
std::shared_ptr<T> ScriptableObject::GetComponent()
{
	auto comp = Registry::Instance().GetComponent<T>(mGO);
	return comp;
}
ScriptableObject::ScriptableObject(GameObject go) : mGO(go)
{
}
void ScriptableObject::SetPosition(glm::vec3 pos) {

};
void ScriptableObject::SetPosition(float x, float y, float z) {

};

Monkey::Monkey(GameObject go) : ScriptableObject(go)
{
	std::cout << "MONKEY CREATED" << std::endl;
}

void Monkey::Init()
{
	std::cout << "MONKEY INIT" << std::endl;
}

void Monkey::OnUpdate(float deltaTime)
{
	std::cout << "MONKEY UPDATE" << std::endl;
}
