#pragma once

#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>
#include "GL/Object.hpp"

namespace Iris::GL
{
    class Shader : protected Object
    {
    public:
        Shader(unsigned int type, const std::string &name, const std::string &suffix, std::shared_ptr<spdlog::logger> logger);
        ~Shader();

        [[nodiscard]] unsigned int GetID() const;
        void Compile() const;

    private:
        const std::string m_name;
        const std::string m_path = "assets/shaders/";
        const std::string m_extension = ".glsl";

        std::shared_ptr<spdlog::logger> m_logger;

        [[nodiscard]] std::string LoadSource() const;
    };
}
