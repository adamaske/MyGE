#pragma once
#include "../System.h"
class QuickCreateObjectSystem : public System {
public:
	virtual void Init() override;

	virtual void OnUpdate(float deltaTime) override;
};