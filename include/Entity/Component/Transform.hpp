#pragma once

#include <glm/ext.hpp>
#include <glm/glm.hpp>

namespace Iris
{
    const glm::mat4 IDENTITY = glm::mat4(1.0f);

    struct Transform
    {
        glm::vec3 position;
        float rotation;
        glm::vec3 scale;

        glm::mat4 GetModel()
        {
            auto model = IDENTITY;
            model = glm::translate(model, position);
            model = glm::rotate(model, rotation, glm::vec3(1.0f));
            model = glm::scale(model, scale);
            return model;
        }
    };
}