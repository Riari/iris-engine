#pragma once

#include <string>
#include <vector>

namespace OGL::Input
{
    class InputBinding
    {
    public:
        InputBinding(std::string label, int primaryKey, int secondaryKey = -1);

        void BindPrimary(int key);

        void BindSecondary(int key);

        std::string GetLabel();

        std::vector<int> GetKeys();

    private:
        std::string m_label;
        int m_primaryKey, m_secondaryKey;
    };
}
