#pragma once

#include "System.h"

class CameraSystem : public System {
public:
    virtual void Init() override;

    virtual void OnUpdate(float deltaTime) override;

    //Can have other functions than this
};

