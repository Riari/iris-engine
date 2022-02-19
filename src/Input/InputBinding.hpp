#pragma once

#include <vector>
#include <GLFW/glfw3.h>

namespace Iris
{
    class InputBinding
    {
    public:
        InputBinding(int id, int primaryKey, int secondaryKey = GLFW_KEY_UNKNOWN);

        void BindPrimary(int key);

        void BindSecondary(int key);

        int GetID();

        std::vector<int> GetKeys();

    private:
        int m_id;
        int m_primary, m_secondary;
    };
}
