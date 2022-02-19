#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "GL/Buffer/VAO.hpp"
#include "GL/Buffer/VBO.hpp"
#include "GL/Shader/ShaderProgram.hpp"

namespace Iris
{
    struct MeshComponent
    {
        std::shared_ptr<VBO> pVbo;
        std::shared_ptr<VAO> pVao;
        glm::vec3 color;
    };
}