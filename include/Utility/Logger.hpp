#pragma once

#include <string>
#include <memory>

#include <spdlog/spdlog.h>

namespace OGL::Utility
{
    class Logger
    {
    public:
        static const std::string PATTERN;
        static const std::shared_ptr<spdlog::logger> GL;
        static const std::shared_ptr<spdlog::logger> MAIN;

        static void Init();
        static std::shared_ptr<spdlog::logger> Create(const char* name);
    };
}
