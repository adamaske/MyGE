#include "pch.h"
#include "ScriptableObject.h"
#include "../Registry.h"
#include "../Components/Components.h"

ScriptableObject::ScriptableObject(GameObject go) : mGO(go)
{
}

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

void ScriptableObject::SetPosition(glm::vec3 pos) {

};
void ScriptableObject::SetPosition(float x, float y, float z) {

};

Monkey::Monkey(GameObject go) : ScriptableObject(go)
{
	//std::cout << "MONKEY CREATED" << std::endl;
}

void Monkey::Init()
{
	//std::cout << "MONKEY INIT" << std::endl;
}

void Monkey::OnUpdate(float deltaTime)
{
	//std::cout << "MONKEY UPDATE" << std::endl;
	if (Input::IsKeyDown(GLFW_KEY_Q)) {
		Logger::Log("MOVE MONKEY UP");
		auto transform = GetComponent<TransformComponent>();
		if (transform) {
			transform->mMatrix = glm::translate(transform->mMatrix, glm::vec3(0, 1 * deltaTime, 0));
		}
	}
	//std::cout << "MONKEY UPDATE" << std::endl;
	if (Input::IsKeyDown(GLFW_KEY_E)) {
		Logger::Log("MOVE MONKEY DOWN");
		auto transform = GetComponent<TransformComponent>();
		if (transform) {
			transform->mMatrix = glm::translate(transform->mMatrix, glm::vec3(0, -1 * deltaTime, 0));
		}
	}
	//std::cout << "MONKEY UPDATE" << std::endl;
	if (Input::IsKeyDown(GLFW_KEY_A)) {
		Logger::Log("MOVE MONKEY LEFT");
		auto transform = GetComponent<TransformComponent>();
		if (transform) {
			transform->mMatrix = glm::translate(transform->mMatrix, glm::vec3(1 * deltaTime, 0, 0));
		}
	}
	//std::cout << "MONKEY UPDATE" << std::endl;
	if (Input::IsKeyDown(GLFW_KEY_D)) {
		Logger::Log("MOVE MONKEY LEFT");
		auto transform = GetComponent<TransformComponent>();
		if (transform) {
			transform->mMatrix = glm::translate(transform->mMatrix, glm::vec3(-1 * deltaTime, 0, 0));
		}
	}
}
