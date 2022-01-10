#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "GL/Shader/ShaderProgram.hpp"
#include "GL/VAO.hpp"
#include "GL/VBO.hpp"

namespace Iris
{
    struct MeshComponent
    {
        std::shared_ptr<VBO> pVbo;
        std::shared_ptr<VAO> pVao;
        glm::vec3 color;
    };
}