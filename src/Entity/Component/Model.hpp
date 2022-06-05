#pragma once

#include <memory>
#include "GL/Model.hpp"

namespace Iris
{
    struct Model
    {
        std::shared_ptr<Model> pModel;
        glm::vec3 color;
    };
}
