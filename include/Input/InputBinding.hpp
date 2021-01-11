#pragma once

#include <string>
#include <vector>

#include <GLFW/glfw3.h>

namespace OGL
{
    class InputBinding
    {
    public:
        InputBinding(std::string name, int primaryKey, int secondaryKey = GLFW_KEY_UNKNOWN);

        void BindPrimary(int key);

        void BindSecondary(int key);

        std::string GetName();

        std::vector<int> GetKeys();

    private:
        std::string m_name;
        int m_primary, m_secondary;
    };
}
