#pragma once
#include "System.h"


class PhysicsSystem : public System {
public:
	virtual void Init() override;
	virtual void OnUpdate(float deltaTime) override;

private:

};