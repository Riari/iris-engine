#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "GL/Buffer/VAO.hpp"
#include "GL/Buffer/VBO.hpp"
#include "GL/Shader/ShaderProgram.hpp"

namespace Iris
{
    struct Mesh
    {
        std::shared_ptr<GL::VBO> pVbo;
        std::shared_ptr<GL::VAO> pVao;
        glm::vec3 color;
    };
}
