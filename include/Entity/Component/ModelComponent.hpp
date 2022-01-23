#pragma once

#include <memory>

#include "GL/Model.hpp"

namespace Iris
{
    struct ModelComponent
    {
        std::shared_ptr<Model> pModel;
        glm::vec3 color;
    };
}