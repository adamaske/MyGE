#pragma once
#include "System.h"
class RenderSystem : public System {
public:
	RenderSystem();
	virtual void Init() override;
	virtual void OnUpdate(float deltaTime) override;
};