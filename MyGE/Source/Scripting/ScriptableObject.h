#pragma once
#include <stdint.h>
#include "Registry.h"
#include "Components.h"
using GameObject = uint32_t;

class ScriptableObject {

public:
	ScriptableObject(GameObject go);

	template<class T>
	void AddComponent();
private:
	GameObject mGO;

};

template<class T>
inline void ScriptableObject::AddComponent()
{
	auto compo = Registry::Instance().RegisterComponent<T>(T(), mGO);

}
