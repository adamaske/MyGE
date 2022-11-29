#pragma once

#include "../Systems/System.h"

class NativeScriptingSystem : public System {
public:
	virtual void Init() override;
	virtual void OnUpdate(float deltaTime) override;





};