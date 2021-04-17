#include "System/System.hpp"

using namespace Iris;

void System::AddEntity(EntityId id)
{
    m_entities.insert(id);
}

void System::RemoveEntity(EntityId id)
{
    m_entities.erase(id);
}

std::list<ComponentType> System::GetComponentTypes()
{
    return {};
}

void System::Update(double)
{
    // noop
}

void System::Update(Window& window, Scene& scene)
{
    // noop
}
