#include <Input/InputBinding.hpp>

namespace OGL::Input
{
    InputBinding::InputBinding(std::string name, int primaryKey, int secondaryKey) :
            m_name(std::move(name)),
            m_primary(primaryKey),
            m_secondary(secondaryKey)
    {}

    void InputBinding::BindPrimary(int key)
    {
        m_primary = key;
    }

    void InputBinding::BindSecondary(int key)
    {
        m_secondary = key;
    }

    std::string InputBinding::GetName()
    {
        return m_name;
    }

    std::vector<int> InputBinding::GetKeys()
    {
        return {m_primary, m_secondary};
    }
}
