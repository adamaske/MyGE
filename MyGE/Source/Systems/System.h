#pragma once

#include <iostream>
#include <fstream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../glm/glm.hpp"
#include "../Components/Components.h"
#include "../Registry.h"
#include "../Vertex.h"
#include "../Buffer.h"
#include "../VertexArray.h"
#include "../ShaderManager.h"
#include "../Textures/Texture.h"
#include "../Textures/TextureManager.h"
#include <stdio.h>
#include <fstream>
#include <sstream>

using GameObject = uint32_t;
class System {
public:
    virtual void Init() = 0;

    virtual void OnUpdate(float deltaTime) = 0;
};

