#include "InputBinding.h"

InputBinding::InputBinding(std::string label, int primaryKey, int secondaryKey) :
        m_label(std::move(label)),
        m_primaryKey(primaryKey),
        m_secondaryKey(secondaryKey)
{}

void InputBinding::BindPrimary(int key)
{
    m_primaryKey = key;
}

void InputBinding::BindSecondary(int key)
{
    m_secondaryKey = key;
}

std::string InputBinding::GetLabel()
{
    return m_label;
}

std::vector<int> InputBinding::GetKeys()
{
    return { m_primaryKey, m_secondaryKey };
}
