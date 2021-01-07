#pragma once

#include <iostream>

#include <glad/glad.h>

#include "../Utility/Logger.h"

using namespace OGL;

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::string strSource;
    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             strSource = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   strSource = "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: strSource = "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     strSource = "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     strSource = "Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           strSource = "Other"; break;
    }

    std::string strType;
    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               strType = "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: strType = "Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  strType = "Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         strType = "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         strType = "Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              strType = "Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          strType = "Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           strType = "Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               strType = "Other"; break;
    }

    std::string strSeverity;
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         strSeverity = "High"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       strSeverity = "Medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          strSeverity = "Low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: strSeverity = "Notification"; break;
    }

    Utility::Logger::GL->error(fmt::format("GL: Error {0} received: {1} (Source: {2}, EventListener: {3}, Severity: {4})", id, message, strSource, strType, strSeverity));
}

void InitGLDebug()
{
    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glDebugMessageCallback(glDebugOutput, NULL);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_FALSE);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, NULL, GL_TRUE);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, NULL, GL_TRUE);
    }

    Utility::Logger::GL->info("Debugging initialized");
}