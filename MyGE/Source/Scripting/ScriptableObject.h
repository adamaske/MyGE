#pragma once
#include <stdint.h>
#include <memory>
#include "../glm/glm.hpp"

using GameObject = uint32_t;

class ScriptableObject {
public:
	ScriptableObject(GameObject go);

	virtual void Init() = 0;
	virtual void OnUpdate(float deltaTime) = 0;

	template<class T>
	std::shared_ptr<T> AddComponent();
	template<class T>
	std::shared_ptr<T> GetComponent();
	
	void SetPosition(glm::vec3 pos);
	void SetPosition(float x, float y, float z);

private:
	GameObject mGO;

};

class Monkey : public ScriptableObject {
public:
	Monkey(GameObject go);
	virtual void Init() override;

	virtual void OnUpdate(float deltaTime) override;
};
