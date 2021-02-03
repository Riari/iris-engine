#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Utility/Logger.hpp"

using namespace Iris;

const std::string Logger::PATTERN = "[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v";
const std::shared_ptr<spdlog::logger> Logger::GL = spdlog::stdout_color_mt("GL");
const std::shared_ptr<spdlog::logger> Logger::MAIN = spdlog::stdout_color_mt("Main");

void Logger::Init()
{
    spdlog::set_pattern(Logger::PATTERN);

#if !defined(NDEBUG)
    spdlog::set_level(spdlog::level::debug);
#endif
}

std::shared_ptr<spdlog::logger> Logger::Create(const char *name)
{
    return spdlog::stdout_color_mt(name);
}
