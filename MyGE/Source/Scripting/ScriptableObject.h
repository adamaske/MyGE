#pragma once
#include <stdint.h>
#include "../Registry.h"
#include "../Components/Components.h"
using GameObject = uint32_t;

class ScriptableObject {

public:
	ScriptableObject(GameObject go);

	template<class T>
	std::shared_ptr<T> AddComponent();
private:
	GameObject mGO;

};

