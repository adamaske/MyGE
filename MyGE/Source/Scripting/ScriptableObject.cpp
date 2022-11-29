#include "ScriptableObject.h"

ScriptableObject::ScriptableObject(GameObject go)  : mGO(go) {
	
}

template<class T>
std::shared_ptr<T> ScriptableObject::AddComponent()
{
	auto comp = Registry::Instance().RegisterComponent<T>(T(), mGO);
	return comp;
}
