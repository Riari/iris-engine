#include "Input/InputBinding.hpp"

using namespace OGL;

InputBinding::InputBinding(int id, int primaryKey, int secondaryKey) :
        m_id(id),
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

int InputBinding::GetID()
{
    return m_id;
}

std::vector<int> InputBinding::GetKeys()
{
    return {m_primary, m_secondary};
}
