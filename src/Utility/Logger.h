#pragma once

namespace OGL::Utility
{
    class Logger
    {
    public:
        static const std::string PATTERN;
        static const std::shared_ptr<spdlog::logger> WINDOW;
        static const std::shared_ptr<spdlog::logger> GL;
        static const std::shared_ptr<spdlog::logger> MAIN;

        static void Init();
    };
}
