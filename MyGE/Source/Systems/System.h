#pragma once

#include <stdint.h>

using GameObject = uint32_t;
class System {
public:
    virtual void Init() = 0;

    virtual void OnUpdate(float deltaTime) = 0;
};

